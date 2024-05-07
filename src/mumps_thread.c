/*
 *
 *  This file is part of MUMPS 5.6.1, released
 *  on Tue Jul 11 07:51:28 UTC 2023
 *
 *
 *  Copyright 1991-2023 CERFACS, CNRS, ENS Lyon, INP Toulouse, Inria,
 *  Mumps Technologies, University of Bordeaux.
 *
 *  This version of MUMPS is provided to you free of charge. It is
 *  released under the CeCILL-C license 
 *  (see doc/CeCILL-C_V1-en.txt, doc/CeCILL-C_V1-fr.txt, and
 *  https://cecill.info/licences/Licence_CeCILL-C_V1-en.html)
 *
 */
#define USLEEP F_SYMBOL(usleep,USLEEP)
#include "mumps_common.h"
#if defined(MUMPS_WIN32)
#    include<windows.h>
     void MUMPS_CALL USLEEP(MUMPS_INT* time)
     {
        /* int* time : in microseconds */
        /* Sleep: milliseconds */
        Sleep((unsigned long)(*time)/1000);
     }
#else
#    include<unistd.h>
     void MUMPS_CALL USLEEP(MUMPS_INT* time)
     {
        /* int* time : in microseconds */
        /* usleep: microseconds */
        usleep((unsigned int)*time);
     }
#endif
