!
!  This file is part of MUMPS 5.7.0, released
!  on Tue Apr 23 10:25:09 UTC 2024
!
!
!  Copyright 1991-2024 CERFACS, CNRS, ENS Lyon, INP Toulouse, Inria,
!  Mumps Technologies, University of Bordeaux.
!
!  This version of MUMPS is provided to you free of charge. It is
!  released under the CeCILL-C license 
!  (see doc/CeCILL-C_V1-en.txt, doc/CeCILL-C_V1-fr.txt, and
!  https://cecill.info/licences/Licence_CeCILL-C_V1-en.html)
!
!
!     Stub mpif.h file including symbols used by MUMPS.
!
      INTEGER MPI_2DOUBLE_PRECISION
      INTEGER MPI_2INTEGER
      INTEGER MPI_2REAL
      INTEGER MPI_ANY_SOURCE
      INTEGER MPI_ANY_TAG
      INTEGER MPI_BYTE
      INTEGER MPI_CHARACTER
      INTEGER MPI_COMM_NULL
      INTEGER MPI_COMM_WORLD
      INTEGER MPI_COMPLEX
      INTEGER MPI_DOUBLE_COMPLEX
      INTEGER MPI_DOUBLE_PRECISION
      INTEGER MPI_INTEGER
      INTEGER MPI_LOGICAL
      INTEGER MPI_MAX
      INTEGER MPI_MAX_PROCESSOR_NAME
      INTEGER MPI_MAXLOC
      INTEGER MPI_MIN
      INTEGER MPI_MINLOC
      INTEGER MPI_PACKED
      INTEGER MPI_PROD
      INTEGER MPI_REAL
      INTEGER MPI_REPLACE
      INTEGER MPI_REQUEST_NULL
      INTEGER MPI_SOURCE
      INTEGER MPI_STATUS_SIZE
      INTEGER MPI_SUM
      INTEGER MPI_TAG
      INTEGER MPI_UNDEFINED
      INTEGER MPI_WTIME_IS_GLOBAL
      INTEGER MPI_LOR
      INTEGER MPI_LAND
      INTEGER MPI_INTEGER8
      INTEGER MPI_REAL8
      INTEGER MPI_COMM_SELF
      INTEGER MPI_BSEND_OVERHEAD
      INTEGER MPI_THREAD_SINGLE
      INTEGER MPI_THREAD_FUNNELED
      INTEGER MPI_THREAD_MULTIPLE
      INTEGER MPI_BOR
      INTEGER MPI_WIN_NULL
      INTEGER MPI_ADDRESS_KIND
      INTEGER MPI_INFO_NULL
      INTEGER MPI_SUCCESS
      INTEGER MPI_ERRORS_RETURN
      PARAMETER (MPI_2DOUBLE_PRECISION=1)
      PARAMETER (MPI_2INTEGER=2)
      PARAMETER (MPI_2REAL=3)
      PARAMETER (MPI_ANY_SOURCE=4)
      PARAMETER (MPI_ANY_TAG=5)
      PARAMETER (MPI_BYTE=6)
      PARAMETER (MPI_CHARACTER=7)
      PARAMETER (MPI_COMM_NULL=8)
      PARAMETER (MPI_COMM_WORLD=9)
      PARAMETER (MPI_COMPLEX=10)
      PARAMETER (MPI_DOUBLE_COMPLEX=11)
      PARAMETER (MPI_DOUBLE_PRECISION=12)
      PARAMETER (MPI_INTEGER=13)
      PARAMETER (MPI_LOGICAL=14)
      PARAMETER (MPI_MAX=15)
      PARAMETER (MPI_MAX_PROCESSOR_NAME=31)
      PARAMETER (MPI_MAXLOC=16)
      PARAMETER (MPI_MIN=17)
      PARAMETER (MPI_MINLOC=18)
      PARAMETER (MPI_PACKED=19)
      PARAMETER (MPI_PROD=20)
      PARAMETER (MPI_REAL=21)
      PARAMETER (MPI_REPLACE=22)
      PARAMETER (MPI_REQUEST_NULL=23)
      PARAMETER (MPI_SOURCE=1)
      PARAMETER (MPI_STATUS_SIZE=2)
      PARAMETER (MPI_SUM=26)
      PARAMETER (MPI_TAG=2)
      PARAMETER (MPI_UNDEFINED=28)
      PARAMETER (MPI_WTIME_IS_GLOBAL=30)
      PARAMETER (MPI_LOR=31)
      PARAMETER (MPI_LAND=32)
      PARAMETER (MPI_INTEGER8=33)
      PARAMETER (MPI_REAL8=34)
      PARAMETER (MPI_COMM_SELF=35)
      PARAMETER (MPI_THREAD_SINGLE=36)
      PARAMETER (MPI_THREAD_FUNNELED=37)
      PARAMETER (MPI_THREAD_MULTIPLE=38)
      PARAMETER (MPI_BOR=39)
      PARAMETER (MPI_WIN_NULL=40)
      PARAMETER (MPI_ADDRESS_KIND=8)
      PARAMETER (MPI_INFO_NULL=41)
      PARAMETER (MPI_SUCCESS=0)
      PARAMETER (MPI_ERRORS_RETURN=42)

      INTEGER MPI_IN_PLACE
      COMMON/mpif_libseq/MPI_IN_PLACE

      PARAMETER (MPI_BSEND_OVERHEAD=0)
      DOUBLE PRECISION MPI_WTIME
      EXTERNAL MPI_WTIME
