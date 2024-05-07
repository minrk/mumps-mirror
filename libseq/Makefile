#
#  This file is part of MUMPS 5.4.1, released
#  on Tue Aug  3 09:49:43 UTC 2021
#
all: libmpiseq

.PHONY: all libmpiseq clean

topdir = ..
include $(topdir)/Makefile.inc

libmpiseq: libmpiseq$(PLAT)$(LIBEXT)

libmpiseq$(PLAT)$(LIBEXT): mpi.o mpic.o elapse.o
	$(AR)$@ mpi.o mpic.o elapse.o
	$(RANLIB) $@
.f.o:
	$(FC) $(OPTF)              -c $*.f $(OUTF)$*.o
.c.o:
	$(CC) $(OPTC) $(CDEFS) -I. -c $*.c $(OUTC)$*.o

clean:
	$(RM) *.o *$(LIBEXT)
