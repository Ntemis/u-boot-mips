/*
 * Copyright (c) 1996-2003 MIPS Technologies, Inc.
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
 * r3041.h: IDT R3041 cp0 registers, and functions to access them.
 */


#ifndef _MIPS_R3041_H_
#define _MIPS_R3041_H_

/* generic R3000 definitions */
#include "mips/r3kc0.h"

/* bus control (cp0 $2) */
#define BUSC_LOCK	0x80000000	/* write lock */
#define BUSC_SET	0x60170300	/* must be set (reserved high) */
#define BUSC_MEM_SH	26		/* MemStrobe Control field shift */
#define   BUSC_CTL_HIGH	  0x0		  /* remain high */
#define   BUSC_CTL_WR	  0x1		  /* on write cycles only */
#define   BUSC_CTL_RD	  0x2		  /* on read cycles only */
#define   BUSC_CTL_RDWR	  0x3		  /* on read and write cycles */
#define BUSC_ED_SH	24		/* ExtDataEn Control field shift */
#define BUSC_IO_SH	22		/* IOStrobe  Control field shift */
#define BUSC_BE16	0x00200000	/* enable BE16(1:0) */
#define BUSC_BE		0x00080000	/* enable BE(3:0) */
#define BUSC_BTA_0	0x00000000	/* bus turnaround (>= 0.5 cycles) */
#define BUSC_BTA_1	0x00004000	/* bus turnaround (>= 1.5 cycles) */
#define BUSC_BTA_2	0x00008000	/* bus turnaround (>= 2.5 cycles) */
#define BUSC_BTA_3	0x0000c000	/* bus turnaround (>= 3.5 cycles) */
#define BUSC_DMA	0x00002000	/* DMA protocol control */
#define BUSC_TC		0x00001000	/* TC control */
#define BUSC_BR		0x00000800	/* BR control */

/* cache configuration (cp0 $3) */
#define CCFG_LOCK	0x80000000	/* write lock */
#define CCFG_SET	0x40000000	/* must be set (reserved high) */
#define CCFG_DBR	0x20000000	/* data block refill enable */
#define CCFG_FDM	0x00080000	/* force dcache miss */

/* portsize (cp0 $10) */
#define PRTSZ_LOCK	0x80000000	/* write lock */

/* port width encodings */
#define PRTSZ_32	0x0		/* 32 bit */
#define PRTSZ_8		0x1		/* 8 bit */
#define PRTSZ_16	0x2		/* 16 bit */

/* memory region shift values */
#define PRTSZ_KSEG2B_SH 28
#define PRTSZ_KSEG2A_SH 26
#define PRTSZ_KUSEGD_SH	24
#define PRTSZ_KUSEGC_SH	22
#define PRTSZ_KUSEGB_SH	20
#define PRTSZ_KUSEGA_SH	18
#define PRTSZ_KSEG1H_SH	14
#define PRTSZ_KSEG1G_SH	12
#define PRTSZ_KSEG1F_SH	10
#define PRTSZ_KSEG1E_SH	8
#define PRTSZ_KSEG1D_SH	6
#define PRTSZ_KSEG1C_SH	4
#define PRTSZ_KSEG1B_SH	2
#define PRTSZ_KSEG1A_SH	0


/* extra CP0 registers */

#ifdef __ASSEMBLER__

#define C0_BUSCTRL	$2
#define C0_CACHECFG	$3
#define C0_COUNT	$9
#define C0_PORTSIZE	$10
#define C0_COMPARE	$11

$busctrl	=	$2
$cachecfg	=	$3
$count		=	$9
$portsize	=	$10
$compare	=	$11

#else

#define C0_BUSCTRL	2
#define C0_CACHECFG	3
#define C0_COUNT	9
#define C0_PORTSIZE	10
#define C0_COMPARE	11

#define r3041_getbusc()		_mips_mfc0(2)
#define r3041_setbusc(v)	_mips_mtc0(2,v)
#define r3041_xchbusc(v)	_mips_mxc0(2,v)
#define r3041_bicbusc(v)	_mips_bcc0(2,v)
#define r3041_bisbusc(v)	_mips_bsc0(2,v)
#define r3041_bcsbusc(c,s)	_mips_bcsc0(2,c,s)

#define r3041_getccfg()		_mips_mfc0(3)
#define r3041_setccfg(v)	_mips_mtc0(3,v)
#define r3041_xchccfg(v)	_mips_mxc0(3,v)
#define r3041_bicccfg(v)	_mips_bcc0(3,v)
#define r3041_bisccfg(v)	_mips_bsc0(3,v)
#define r3041_bcsccfg(c,s)	_mips_bcsc0(3,c,s)

#define r3041_getprtsz()	_mips_mfc0(10)
#define r3041_setprtsz(v)	_mips_mtc0(10,v)
#define r3041_xchprtsz(v)	_mips_mxc0(10,v)

#endif /* __ASSEMBLER__ */

#endif /* _MIPS_R3041_H_ */
