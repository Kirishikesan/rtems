/*
 *  SBC5206 bsp_cleanup
 *
 *  This routine returns control from RTEMS to the monitor.
 *
 *  Author:
 *    David Fiddes, D.J@fiddes.surfaid.org
 *    http://www.calm.hw.ac.uk/davidf/coldfire/
 *
 *  COPYRIGHT (c) 1989-1998.
 *  On-Line Applications Research Corporation (OAR).
 *  Copyright assigned to U.S. Government, 1994.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 * 
 *  http://www.OARcorp.com/rtems/license.html.
 * 
 *  $Id$
 */

#include <rtems.h>
#include <bsp.h>
#include <rtems/bspIo.h>

void bsp_cleanup( void )
{
    bsp_reset(0);
}
