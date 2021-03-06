/**************************************************************************

Copyright (c) 2001-2005, Intel Corporation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 3. Neither the name of the Intel Corporation nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/

/*$FreeBSD: /repoman/r/ncvs/src/sys/dev/em/if_em_osdep.h,v 1.14 2005/05/26 23:32:02 tackerman Exp $*/

#ifndef _RTEMS_OS_H_
#define _RTEMS_OS_H_

#include <rtems.h>
#include "../porting/rtemscompat.h"

#include <sys/types.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/malloc.h>
#include <sys/kernel.h>
#include <bsp/pci.h>

/* Eventually, we should include this
#include <rtems/rtems-mii-ioctl.h>
*/
#define IFM_LINK_OK     IFM_FLAG0
#define IFM_ANEG_DIS    IFM_FLAG1

#define ASSERT(x) if(!(x)) panic("EM: x")

/* The happy-fun DELAY macro is defined in /usr/src/sys/i386/include/clock.h */
#define usec_delay(x) DELAY(x)
#define msec_delay(x) DELAY(1000*(x))
/* TODO: Should we be paranoid about delaying in interrupt context? */
#define msec_delay_irq(x) DELAY(1000*(x))

#define MSGOUT(S, A, B)     printf(S "\n", A, B)
#define DEBUGFUNC(F)        DEBUGOUT(F);
#if DBG
	#define DEBUGOUT(S)         printf(S "\n")
	#define DEBUGOUT1(S,A)      printf(S "\n",A)
	#define DEBUGOUT2(S,A,B)    printf(S "\n",A,B)
	#define DEBUGOUT3(S,A,B,C)  printf(S "\n",A,B,C)
	#define bootverbose	(1)
	#define DEBUGOUT7(S,A,B,C,D,E,F,G)  printf(S "\n",A,B,C,D,E,F,G)
#else
	#define DEBUGOUT(S)
	#define DEBUGOUT1(S,A)
	#define DEBUGOUT2(S,A,B)
	#define DEBUGOUT3(S,A,B,C)
	#define bootverbose	(0)
	#define DEBUGOUT7(S,A,B,C,D,E,F,G)
#endif

#define CMD_MEM_WRT_INVALIDATE          0x0010  /* BIT_4 */
#define PCI_COMMAND_REGISTER            PCIR_COMMAND

struct em_osdep
{
	unsigned           mem_bus_space_handle;
	device_t           dev;
};

struct rtems_ifmedia {
	int	ifm_media;
};

#define E1000_WRITE_FLUSH(hw) E1000_READ_REG(hw, STATUS)

/* Read from an absolute offset in the adapter's memory space */
#define E1000_READ_OFFSET(hw, offset) \
    bus_space_read_4( ((struct em_osdep *)(hw)->back)->mem_bus_space_tag, \
                      ((struct em_osdep *)(hw)->back)->mem_bus_space_handle, \
                      offset)

/* Write to an absolute offset in the adapter's memory space */
#define E1000_WRITE_OFFSET(hw, offset, value) \
    bus_space_write_4( ((struct em_osdep *)(hw)->back)->mem_bus_space_tag, \
                       ((struct em_osdep *)(hw)->back)->mem_bus_space_handle, \
                       offset, \
                       value)

/* Convert a register name to its offset in the adapter's memory space */
#define E1000_REG_OFFSET(hw, reg) \
    ((hw)->mac_type >= em_82543 ? E1000_##reg : E1000_82542_##reg)

#define E1000_READ_REG(hw, reg) \
    E1000_READ_OFFSET(hw, E1000_REG_OFFSET(hw, reg))

#define E1000_WRITE_REG(hw, reg, value) \
    E1000_WRITE_OFFSET(hw, E1000_REG_OFFSET(hw, reg), value)

#define E1000_READ_REG_ARRAY(hw, reg, index) \
    E1000_READ_OFFSET(hw, E1000_REG_OFFSET(hw, reg) + ((index) << 2))

#define E1000_READ_REG_ARRAY_DWORD E1000_READ_REG_ARRAY

#define E1000_WRITE_REG_ARRAY(hw, reg, index, value) \
    E1000_WRITE_OFFSET(hw, E1000_REG_OFFSET(hw, reg) + ((index) << 2), value)

#define E1000_WRITE_REG_ARRAY_BYTE(hw, reg, index, value) \
    bus_space_write_1( ((struct em_osdep *)(hw)->back)->mem_bus_space_tag, \
                       ((struct em_osdep *)(hw)->back)->mem_bus_space_handle, \
                       E1000_REG_OFFSET(hw, reg) + (index), \
                       value)

#define E1000_WRITE_REG_ARRAY_WORD(hw, reg, index, value) \
    bus_space_write_2( ((struct em_osdep *)(hw)->back)->mem_bus_space_tag, \
                       ((struct em_osdep *)(hw)->back)->mem_bus_space_handle, \
                       E1000_REG_OFFSET(hw, reg) + (index), \
                       value)

#define E1000_WRITE_REG_ARRAY_DWORD(hw, reg, index, value) \
    E1000_WRITE_OFFSET(hw, E1000_REG_OFFSET(hw, reg) + ((index) << 2), value)

#endif  /* _FREEBSD_OS_H_ */

