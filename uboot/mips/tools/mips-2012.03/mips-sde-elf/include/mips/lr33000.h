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
 * lsi/lr33000.h: defines for LSI Logic LR33000
 */


#ifndef _MIPS_LR33000_H_
#define _MIPS_LR33000_H_

#ifdef __cplusplus
extern "C" {
#endif

/* generic R3000 definitions */
#include "mips/r3kc0.h"

#define DEBUG_VECT	0x040
#define K0_DEBUG_VECT	(KSEG0_BASE + DEBUG_VECT)
#define K1_DEBUG_VECT	(KSEG1_BASE + DEBUG_VECT)

/* definitions for DCIC register bits */
#define DCIC_TR	0x80000000	/* Trap enable */
#define DCIC_UD	0x40000000	/* User debug enable */
#define DCIC_KD	0x20000000	/* Kernel debug enable */
#define DCIC_TE	0x10000000	/* Trace enable */
#define DCIC_DW	0x08000000	/* Enable data breakpoints on write */
#define DCIC_DR	0x04000000	/* Enable data breakpoints on read */
#define DCIC_DAE 0x02000000	/* Enable data addresss breakpoints */
#define DCIC_PCE 0x01000000	/* Enable instruction breakpoints */
#define DCIC_DE	0x00800000	/* Debug enable */
#define DCIC_D	0x00002000	/* Data cache invalidate enable */
#define DCIC_I	0x00001000	/* Instruction cache invalidate enable */
#define DCIC_T	0x00000020	/* Trace, set by CPU */
#define DCIC_W	0x00000010	/* Write reference, set by CPU */
#define DCIC_R	0x00000008	/* Read reference, set by CPU */
#define DCIC_DA	0x00000004	/* Data address, set by CPU */
#define DCIC_PC	0x00000002	/* Program counter, set by CPU */
#define DCIC_DB	0x00000001	/* Debug, set by CPU */


/* Define counter/timer register addresses */
#define M_TIC1	0xfffe0000	/* timer 1 initial count */
#define M_TC1	0xfffe0004	/* timer 1 control	 */
#define M_TIC2	0xfffe0008	/* timer 2 initial count */
#define M_TC2	0xfffe000c	/* timer 2 control	 */
#define M_RTIC	0xfffe0010	/* refresh timer	 */
#define M_CFGREG	0xfffe0020	/* configuration reg	 */

/* Definitions for counter/timer control register bits */
#define TC_CE	 0x00000004	/* count enable */
#define TC_IE	 0x00000002	/* interrupt enable */
#define TC_INT 	 0x00000001	/* interrupt request */

/* Definitions for Configuration register bits */
#define CR_WBE		0x80000000	/* write buffer enable */
#define CR_BEN 		0x40000000	/* block write enable */
#define CR_PGSZMSK 	0x38000000	/* page size mask */
#define CR_PGSZSHFT 	27		/* page size shift amount */
#define CR_IW8 		0x02000000	/* add 8 cycles to IOWAIT */
#define CR_PW8		0x01000000	/* add 8 cycles to PWAIT */
#define CR_ICDISABLE	0x00800000	/* Instruction cache disable */
#define CR_DCDISABLE	0x00400000	/* Data cache disable */
#define CR_IBLK_2	0x00000000	/* Instruction cache block size */
#define CR_IBLK_4	0x00100000	/* Instruction cache block size */
#define CR_IBLK_8	0x00200000	/* Instruction cache block size */
#define CR_IBLK_16	0x00300000	/* Instruction cache block size */
#define CR_IBLKMSK	0x00300000	/* Instruction cache block size */
#define CR_DBLK_2	0x00000000	/* Data cache block size */
#define CR_DBLK_4	0x00040000	/* Data cache block size */
#define CR_DBLK_8	0x00080000	/* Data cache block size */
#define CR_DBLK_16	0x000c0000	/* Data cache block size */
#define CR_DBLKMSK	0x000c0000	/* Data cache block size */
#define CR_IODIS	0x00020000	/* Disable DRDY for I/O addresses */
#define CR_IOWAITSHFT	13		/* I/O wait states */
#define CR_PDIS		0x00001000	/* Disable DRDY for PROM addresses */
#define CR_PWAITSHFT	8		/* PROM wait states */
#define CR_DPEN		0x00000040	/* Enable parity check for DRAM */
#define CR_RDYGEN	0x00000020	/* Disable DRDY for DRAM addresses */
#define CR_BLKFDIS	0x00000010	/* Disable DRAM block refill */
#define CR_RFSHEN	0x00000008	/* Enable refresh generator */
#define CR_RASPCHG	0x00000004	/* Define RAS precharge */
#define CR_CASLNTH	0x00000002	/* Define CAS active time */
#define CR_DRAMEN	0x00000001	/* Enable DRAM controller */

/* extra CP0 registers */

#ifdef __ASSEMBLER__

#define C0_BPC	$3		/* breakpoint on instr */
#define C0_BDA	$5		/* breakpoint on data */
#define C0_DCIC	$7		/* cache control */

$bpc	=	$3
$bda	=	$5
$dcic	=	$7

#else

#define C0_BPC	3		/* breakpoint on instr */
#define C0_BDA	5		/* breakpoint on data */
#define C0_DCIC	7		/* cache control */

#define lr33k_getbpc()		_mips_mfc0(3)
#define lr33k_setbpc(v)		_mips_mtc0(3,v)
#define lr33k_xchbpc(v)		_mips_mxc0(3,v)

#define lr33k_getbda()		_mips_mfc0(5)
#define lr33k_setbda(v)		_mips_mtc0(5,v)
#define lr33k_xchbda(v)		_mips_mxc0(5,v)

#define lr33k_getdcic()		_mips_mfc0(7)
#define lr33k_setdcic(v)	_mips_mtc0(7,v)
#define lr33k_xchdcic(v)	_mips_mxc0(7,v)
#define lr33k_bicdcic(v)	_mips_bcc0(7,v)
#define lr33k_bisdcic(v)	_mips_bsc0(7,v)
#define lr33k_bcsdcic(c,s)	_mips_bcsc0(7,c,s)

#define TIC1   (*((volatile unsigned *)M_TIC1)) /* timer 1 initial count */
#define TC1    (*((volatile unsigned *)M_TC1))  /* timer 1 control	 */
#define TIC2   (*((volatile unsigned *)M_TIC2)) /* timer 2 initial count */
#define TC2    (*((volatile unsigned *)M_TC2))  /* timer 2 control */
#define RTIC   (*((volatile unsigned *)M_RTIC)) /* refresh timer */
#define CFGREG (*((volatile unsigned *)M_CFGREG)) /* configuration reg */

#endif /* __ASSEMBLER */


#ifdef __cplusplus
}
#endif
#endif /* _MIPS_LR33000_H_ */
