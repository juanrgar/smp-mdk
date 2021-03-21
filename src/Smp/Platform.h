//
// Title:
//      Platform.h
//
// Project:
//      Simulation Model Portability (SMP) Standard 2.0
//      C++ Mapping
//      Version 1.2 from October 28th, 2005
//
// Origin:
//      Simulation Model Portability (SMP) Configuration Control Board (CCB)
//
// Purpose:
//      This file defines global includes, settings and macros for Smp.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_PLATFORM_H
#define SMP_PLATFORM_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include <assert.h>

#if defined (__linux__) || defined (__CYGWIN__)
    #include <sys/types.h>
    #include <ctype.h>
    #include <stdint.h>
#elif defined (__sgi)
    #include <inttypes.h>
#endif

// ---------------------------------------------------------------------------
// --------------------------- Constant Declarations -------------------------
// ---------------------------------------------------------------------------

#ifdef  WIN32
    #ifndef NULL
    #define NULL 0
    #endif
#endif

// ---------------------------------------------------------------------------
// --------------------------- Platform Specific Types -----------------------
// ---------------------------------------------------------------------------

// Check __CYGWIN__ case before WIN32, because xercesc\util\AutoSense.hpp 
// defines WIN32 in __CYGWIN__ case. Hence both, __CYGWIN__ and WIN32, are
// defined in the __CYGWIN__ case, if AutoSense.hpp is included.
#if defined (__linux__) || defined (__CYGWIN__)
    typedef int64_t             int64;      ///< 64 bit   signed integer type.
    typedef uint64_t            uint64;     ///< 64 bit unsigned integer type.
    #define PATH_SEPARATOR      '/'

    #ifndef INT64_MIN
    #define INT64_MIN   LLONG_MIN
    #endif
    #ifndef INT64_MAX
    #define INT64_MAX   LLONG_MAX
    #endif

#elif defined (__sgi)
    typedef int64_t             int64;      ///< 64 bit   signed integer type.
    typedef uint64_t            uint64;     ///< 64 bit unsigned integer type.
    #define PATH_SEPARATOR      '/'

#elif defined (__APPLE__) && defined (__MACH__)
    typedef int64_t             int64;      ///< 64 bit   signed integer type.
    typedef uint64_t            uint64;     ///< 64 bit unsigned integer type.
    #define PATH_SEPARATOR      '/'

#elif defined (WIN32)
    typedef __int64             int64;      ///< 64 bit   signed integer type.
    typedef unsigned __int64    uint64;     ///< 64 bit unsigned integer type.

    #ifndef INT64_MIN
    #define INT64_MIN   LLONG_MIN
    #endif
    #ifndef INT64_MAX
    #define INT64_MAX   LLONG_MAX
    #endif

    #define PATH_SEPARATOR      '\\'
#endif

#endif  // SMP_PLATFORM_H

/***********
 * History *
 ***********/

//$Log: Platform.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

