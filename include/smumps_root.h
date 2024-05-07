!
!  This file is part of MUMPS 5.2.1, released
!  on Fri Jun 14 14:46:05 UTC 2019
!
!
!  Copyright 1991-2019 CERFACS, CNRS, ENS Lyon, INP Toulouse, Inria,
!  Mumps Technologies, University of Bordeaux.
!
!  This version of MUMPS is provided to you free of charge. It is
!  released under the CeCILL-C license:
!  http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html
!
      TYPE SMUMPS_ROOT_STRUC
        SEQUENCE
        INTEGER :: MBLOCK, NBLOCK, NPROW, NPCOL
        INTEGER :: MYROW, MYCOL
        INTEGER :: SCHUR_MLOC, SCHUR_NLOC, SCHUR_LLD
        INTEGER :: RHS_NLOC
        INTEGER :: ROOT_SIZE, TOT_ROOT_SIZE
!       descriptor for scalapack
        INTEGER, DIMENSION( 9 ) :: DESCRIPTOR
        INTEGER :: CNTXT_BLACS, LPIV, rootpad0
        INTEGER, DIMENSION(:), POINTER :: RG2L_ROW
        INTEGER, DIMENSION(:), POINTER :: RG2L_COL
        INTEGER , DIMENSION(:), POINTER :: IPIV, rootpad1
!       Centralized master of root
        REAL, DIMENSION(:), POINTER :: RHS_CNTR_MASTER_ROOT
!       Used to access Schur easily from root structure
        REAL, DIMENSION(:), POINTER :: SCHUR_POINTER
!       for try_null_space preprocessing constant only:
        REAL, DIMENSION(:), POINTER :: QR_TAU, rootpad2
!       Fwd in facto: 
!           case of scalapack root: to store RHS in 2D block cyclic
!           format compatible with root distribution
        REAL, DIMENSION(:,:), POINTER :: RHS_ROOT, rootpad
!       for try_nullspace preprocessing constant only:
        REAL :: QR_RCOND, rootpad3
        LOGICAL :: yes, gridinit_done
!       for SVD on root (#define try_null_space)
        REAL, DIMENSION(:,:), POINTER :: SVD_U, SVD_VT
!       for RR on root (#define try_null_space)
        REAL, DIMENSION(:), POINTER :: SINGULAR_VALUES
        INTEGER :: NB_SINGULAR_VALUES,rootpad4
!
      END TYPE SMUMPS_ROOT_STRUC
