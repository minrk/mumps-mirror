import os
import re
import shutil
import tarfile
from functools import lru_cache
from pathlib import Path
from tempfile import TemporaryDirectory

import appdirs
import click
import requests
from bs4 import BeautifulSoup
from git import Repo
from tqdm import tqdm

mirror_branch = "mirror"  # the branch containing the mirror
cache_dir = Path(appdirs.user_cache_dir()) / "mumps-mirror"
changelog_url = "https://mumps-solver.org/index.php?page=dwnld"

if os.getenv("GITHUB_ACTION"):
    repo_url = f"{os.environ['GITHUB_SERVER_URL']}/{os.environ['GITHUB_REPOSITORY']}"
    # run in local checkout on GitHub actions
    repo_path = Path.cwd()
    run_url = f"{os.environ['GITHUB_SERVER_URL']}/{os.environ['GITHUB_REPOSITORY']}/actions/runs/{os.environ['GITHUB_RUN_ID']}"
else:
    repo_url = "git@github.com:minrk/mumps-mirror"
    repo_path = cache_dir / "repo"
    run_url = ""


_skip_versions = {"5.1.0"}  # doesn't appear to be published

# some versions don't appear to be on mumps-solver.org
_lyon_versions = {
    "5.0.1",
    "5.0.2",
    "5.1.1",
    "5.3.0",
    "5.3.1",
    "5.3.3",
    "5.3.4",
    "5.4.0",
    "5.5.0",
}


@lru_cache
def _v(version: str) -> tuple[int]:
    """Version string to sortable tuple of ints"""
    return tuple(int(part) for part in re.compile("(\d+)").findall(version))


def url_for_version(version: str) -> str:
    """Download URL for a mumps version"""
    if version in _lyon_versions:
        return f"https://graal.ens-lyon.fr/MUMPS/MUMPS_{version}.tar.gz"
    else:
        return f"https://mumps-solver.org/MUMPS_{version}.tar.gz"


def list_versions(cutoff: str = "4.999") -> list[str]:
    """Fetch changelog and list available versions"""
    r = requests.get(changelog_url)
    versions = set()
    page = BeautifulSoup(r.text, "html.parser")
    for heading in page.find_all("h5"):
        if heading.string.startswith("Changes"):
            for vs in re.findall(r"\b([\d\.]+\d+)$", heading.string):
                versions.add(vs)
    cutoff_v = _v(cutoff)
    version_list = sorted(v for v in versions if _v(v) > cutoff_v)
    return version_list


def clone(repo_path: Path | str = repo_path, clean: bool = False) -> None:
    """Clone the mirror repo"""
    repo_path = Path(repo_path)
    if clean and repo_path.exists():
        print(f"Removing {repo_path}")
        shutil.rmtree(repo_path)
    if repo_path.exists():
        repo = Repo(repo_path)
    else:
        print(f"Cloning {repo_url} -> {repo_path}")
        repo = Repo.clone_from(repo_url, repo_path)

    origin = repo.remote()
    origin.fetch()
    remote_branch = getattr(origin.refs, mirror_branch)
    try:
        branch = getattr(repo.refs, mirror_branch)
    except AttributeError:
        branch = repo.create_head(mirror_branch, remote_branch)
    branch.set_tracking_branch(remote_branch)
    branch.checkout()
    origin.pull(mirror_branch, ff_only=True)
    if repo.untracked_files:
        raise RuntimeError(f"Untracked files: {repo.untracked_files}")


def list_tags(repo_path: Path | str) -> list[str]:
    """List tags in the mirror"""
    repo = Repo(repo_path)
    return sorted([tag.name for tag in repo.tags], key=_v)


def download(url: str, no_cache=False) -> Path:
    """Download a URL to cache directory

    If `no_cache`, clear cache
    """
    fname = url.rsplit("/", 1)[-1]
    dest = cache_dir / fname
    cache_dir.mkdir(parents=True, exist_ok=True)
    if no_cache and dest.exists():
        dest.unlink()
    if dest.exists():
        print(f"Using cached {fname}")
        return dest
    dest_temp = dest.with_suffix(".tmp")
    with requests.get(url, stream=True) as r:
        r.raise_for_status()
        total = int(r.headers.get("Content-Length"), 0)

        with dest_temp.open("wb") as f, tqdm(
            desc=f"Downloading {fname}",
            total=total,
            unit="B",
            unit_scale=True,
        ) as progress:
            for chunk in r.iter_content(1024):
                progress.update(len(chunk))
                f.write(chunk)
    dest_temp.rename(dest)
    return dest


def clear_repo(repo_path):
    """Remove all tracked files from the repo"""
    repo = Repo(repo_path)
    paths = []
    for (path, stage), _entry in repo.index.entries.items():
        paths.append(path)
    print(f"Removing {len(paths)} files")
    repo.index.remove(paths, working_tree=True)


def add_version(repo_path: Path, version: str, no_cache=False):
    print(f"Adding version {version}")
    url = url_for_version(version)
    tarball_path = download(url, no_cache=no_cache)
    clear_repo(repo_path)
    with TemporaryDirectory() as td:
        td = Path(td)
        with tarfile.open(tarball_path) as tf:
            tf.extractall(td)
        top_level = list(td.glob("MUMPS*"))
        if len(top_level) != 1:
            print(f"Unexpected top-level contents: {top_level}")
        mumps_dir = top_level[0]
        for path in mumps_dir.glob("*"):
            path.rename(repo_path / path.name)
        # make sure we left an empty dir
        mumps_dir.rmdir()
    repo = Repo(repo_path)
    new_files = repo.untracked_files
    print(f"Adding {len(new_files)} files")
    repo.index.add(repo.untracked_files)
    message = f"Mirror MUMPS {version}"
    if run_url:
        message = message + f"\n\nCreated by {run_url}"
    repo.index.commit(message)
    repo.create_tag(version, message=message)


@click.command()
@click.option("--clean", is_flag=True, help="Start with a clean checkout")
@click.option("--no-cache", is_flag=True, help="Disable download cache")
@click.option("--push", is_flag=True, help="Push changes")
def main(clean, no_cache, push):
    print(f"Working in {repo_path}")
    clone(repo_path, clean=clean)
    existing_tags = list_tags(repo_path)
    print(f"Have versions: {existing_tags}")
    available_versions = list_versions()
    print(f"Available versions: {available_versions}")
    if existing_tags:
        latest_tag = existing_tags[-1]
    else:
        latest_tag = "4.9999"

    missing_versions = [
        v
        for v in available_versions
        if (v not in (set(existing_tags) | _skip_versions) and _v(v) < _v(latest_tag))
    ]
    if missing_versions:
        print(f"Missing versions: {missing_versions}")
    new_versions = [
        v
        for v in available_versions
        if _v(v) > _v(latest_tag) and v not in _skip_versions
    ]
    if not new_versions:
        print("Up-to-date")
        return
    print(f"New versions to add: {new_versions}")
    repo = Repo(repo_path)
    for version in new_versions:
        add_version(repo_path, version, no_cache=no_cache)
        if push:
            print(f"Pushing {version}")
            repo.remotes.origin.push(mirror_branch, follow_tags=True)


if __name__ == "__main__":
    main()
