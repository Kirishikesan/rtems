/*
 *  COPYRIGHT (c) 1994 by Division Incorporated
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>

#if defined(RTEMS_NEWLIB)
#include <stdio.h>
#include <unistd.h>

  #if defined(__USE_INIT_FINI__)
    #if CPU_USE_LIBC_INIT_FINI_ARRAY == TRUE
      #define FINI_SYMBOL __libc_fini_array
    #else
      #define FINI_SYMBOL _fini
    #endif

    extern void FINI_SYMBOL( void );
  #endif

void _exit(int status)
{
  /*
   *  If the toolset uses init/fini sections, then we need to
   *  run the global destructors now.
   */
  #if defined(FINI_SYMBOL)
    FINI_SYMBOL();
  #endif

  rtems_shutdown_executive(status);
  /* does not return */
}

#endif
