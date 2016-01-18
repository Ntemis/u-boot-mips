/*
 * Copyright (c) 1999-2003 MIPS Technologies, Inc.
 * Copyright (C) 2009 CodeSourcery, LLC.
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *      copyright
 *        notice, this list of conditions and the following disclaimer
 *        in the documentation and/or other materials provided with
 *        the distribution.
 *      * Neither the name of MIPS Technologies Inc. nor the names of its
 *        contributors may be used to endorse or promote products derived
 *        from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* 
 * lsi/tr4102.h: definitions for LSI Logic TinyRISC TR4102
 */


#ifndef _MIPS_TR4102_H_
#define _MIPS_TR4102_H_

#ifdef __cplusplus
extern "C" {
#endif

/* tr4102 = tr4101 + r3000 mmu + extensions */
#if !#mmu(no)
/* XXX is this true, or is it like the cw401x */
#assert mmu(r3k)
#endif
#include "mips/tr4101.h"

/* BSYS_SCR register gains some extra bits */
#define SCR_MMU  	(1<<31)		/* mmu enable? */
#define SCR_DSNPEN 	(1<<29)		/* data cache snoop enable */
#define SCR_ISNPEN 	(1<<28)		/* insn cache snoop enable */
#define SCR_INTCONDMASK (15<<16)
#define SCR_CPC3EN	(1<<19) 	/* connect Cpc3 to int */
#define SCR_CPC2EN	(1<<18) 	/* connect Cpc2 to int */
#define SCR_CPC1EN	(1<<17) 	/* connect Cpc1 to int */
#define SCR_CPC0EN	(1<<16) 	/* connect Cpc0 to int */

/* 
 * New system configuration #2 
 */
#define BSYS_SCR2	0xbfff0004	

#define SCR2_TMRIE1 	(1<<21) /* TINT1E */
#define SCR2_TMRIE0 	(1<<20) /* TINT0E */
#define SCR2_MRR 	(1<<19)
#define SCR2_4101C 	(1<<17)
#define SCR2_MDUSATE  	(1<<16)
#define SCR2_MDUSATI  	(1<<15)
#define SCR2_FDBSTOP  	(1<<14)
#define SCR2_CLKDBMASK  (15<<7)
#define SCR2_CLKDDMASK  (3<<5)
#define SCR2_CLKSEL  	(1<<4)
#define SCR2_CLKPLLE  	(1<<3)
#define SCR2_CLKST  	(1<<2)
#define SCR2_CLKDCMASK  (3<<0)

/* Timer gains some extra control bits */
#define TMODE_E0	(1<<0)	/* timer enable */
#define TMODE_P0	(1<<1)	/* pulse (vs toggle) mode */
#define TMODE_M0	(1<<2)	/* watchdog mode */
#define TMODE_I0	(1<<3)	/* invert output */
#define TMODE_S0	(1<<4)	/* stop on zero */
#define TMODE_D0	(1<<5)	/* stop when debug mode */
#define TMODE_MASK0      0x3f

#define TMODE_E1	(1<<8)	/* timer enable */
#define TMODE_P1	(1<<9)	/* pulse (vs toggle) mode */
#define TMODE_M1	(1<<10)	/* watchdog mode */
#define TMODE_I1	(1<<11)	/* invert output */
#define TMODE_S1	(1<<12)	/* stop on zero */
#define TMODE_D1	(1<<13)	/* stop when debug mode */
#define TMODE_MASK1     (0x3f<<8)

/* FBUS */
#define M_FACFG0 0xbfff0400	/* address range 0 */
#define M_FACFG1 0xbfff0404	/* address range 1 */
#define M_FACFG2 0xbfff0408	/* address range 2 */
#define M_FACFG3 0xbfff040c	/* address range 3 */
#define M_FACFG4 0xbfff0410	/* address range 4 */
#define M_FACFG5 0xbfff0414	/* address range 5 */
#define M_FBUSTA 0xbfff0418	/* Bus Turnaround */
#define M_FACMP0 0xbfff0440	/* address range 0 comparitor */
#define M_FACMP1 0xbfff0444	/* address range 1 comparitor */
#define M_FACMP2 0xbfff0448	/* address range 2 comparitor */
#define M_FACMP3 0xbfff044c	/* address range 3 comparitor */
#define M_FACMP4 0xbfff0450	/* address range 4 comparitor */
#define M_FACMP5 0xbfff0454	/* address range 5 comparitor */
#define M_FBUSCMP 0xbfff0470	/* address compare register for Fbus */
#define M_FBUSAC 0xbfff0474	/* address compare register for memory etc */
#define M_FBUSCFG 0xbfff0480	/* config for non 0-5 range  */
#define M_FBURST 0xbfff0484	/* timing for burst mode  */
#define M_FSFLASH 0xbfff0488	/* timing for flash */
#define M_FSDRAM 0xbfff0490	/* cfg for edo sdram */
#define M_FDRAMT 0xbfff0494	/* timing for edo dram */
#define M_FSDRAMT 0xbfff0498	/* timing for sdram */
#define M_FSDRAM2 0xbfff049c	/* cfg for sdram */
#define M_FGPCFG 0xbfff04c0	/* cfg for gpio */
#define M_FGPOUTPUT 0xbfff04c4	/* output for gpio */
#define M_FGPINPUT 0xbfff04c8	/* input for gpio */

#define FACFG_WIDTH_8	(0<<30)
#define FACFG_WIDTH_16	(1<<30)
#define FACFG_WIDTH_32	(2<<30)
#define FACFG_GPSEL	(1<<29)
#define FACFG_RAMFLSH	(1<<28)
#define FACFG_RDADMASK	(7<<25)
#define FACFG_RDDDMASK	(3<<23)
#define FACFG_WRADMASK	(7<<20)
#define FACFG_WRDDMASK	(3<<18)
#define FACFG_CSRADMASK	(7<<15)
#define FACFG_CSWADMASK	(7<<12)
#define FACFG_CSRDDMASK	(3<<10)
#define FACFG_CSWDDMASK	(3<<8)
#define FACFG_BURST	(1<<7)
#define FACFG_XACK	(1<<6)
#define FACFG_WAIT_15	(15<<1)
#define FACFG_WAITMASK	(0x1f<<1)
#define FACFG_EN	(1<<0)

#define FACMP_MASK  	(0x1fff<<16)
#define FACMP_ADDRMASK   0xffff

#if 0 /* FACMP examples */
00001fbc        64KB starting at 1fbc0000 (default boot prom)
001f1fc0	2MB starting at 1fc00000   (boot prom)
00ff0000	16MB starting at 00000000  (SDRAM for Primary RAM)
07ff0000	128MB starting at 00000000  (SDRAM for Primary RAM)
00010000        128KB starting at 00000000 (SRAM for Primary RAM)
00ff0100	16MB starting at 01000000  (SDRAM at a1000000)
00010100	128KB starting at 01000000  (SRAM at a1000000)
00010e00	128KB starting at 0e000000  (SRAM at ae000000)
00001fbf        64KB starting at 1fbf0000
00001e00        64KB starting at 1e000000 (UART at be000000)
00001c00        64KB starting at 1c000000 (Ether at bc000000)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _MIPS_TR4102_H_ */
