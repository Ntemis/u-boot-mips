/*
 * Copyright (c) 1996-2006 MIPS Technologies, Inc.
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
 * r4650.h : MIPS SDE R4650/R4640 coprocessor 0 definitions
 */


#ifndef _MIPS_R4650_H_
#define _MIPS_R4650_H_

#ifdef __cplusplus
extern "C" {
#endif

/* This CPU only has a BAT type MMU */
#assert mmu(no)
#include "mips/notlb.h"

/*
 * R4650 Exception Codes
 */
#define EXC_INTR	0	/* interrupt */
#define EXC_RES1	1
#define EXC_IBOUND	2	/* instruction bounds error */
#define EXC_DBOUND	3	/* data bounds error */
#define EXC_ADEL	4	/* address error (load/i-fetch) */
#define EXC_ADES	5	/* address error (store) */
#define EXC_IBE		6	/* bus error (i-fetch) */
#define EXC_DBE		7	/* data bus error (load/store) */
#define EXC_SYS		8	/* system call */
#define EXC_BP		9	/* breakpoint */
#define EXC_RI		10	/* reserved instruction */
#define EXC_CPU		11	/* coprocessor unusable */
#define EXC_OVF		12	/* integer overflow */
#define EXC_TRAP	13	/* trap exception */
#define EXC_RES14	14
#define EXC_FPE		15	/* floating point exception */
#define EXC_RES16	16
#define EXC_RES17	17
#define EXC_RES18	18
#define EXC_RES19	19
#define EXC_RES20	20
#define EXC_RES21	21
#define EXC_RES22	22
#define EXC_WATCH	23	/* watchpoint */
#define EXC_RES24	24
#define EXC_RES25	25
#define EXC_RES26	26
#define EXC_RES27	27
#define EXC_RES28	28
#define EXC_RES29	29
#define EXC_RES30	30
#define EXC_RES31	31


/*
 * R4650 Cause Register 
 */
#define CR_BD		0x80000000	/* branch delay */
#define CR_CEMASK	0x30000000      /* coprocessor used */
#define CR_CESHIFT	28

#define CR_DW		0x02000000      /* DWatch matched */
#define CR_IW		0x01000000      /* IWatch matched */
#define CR_IV		0x00800000      /* dedicated i/u vector */

/* interrupt pending bits */
#define CR_SINT0	0x00000100 	/* s/w interrupt 0 */
#define CR_SINT1	0x00000200	/* s/w interrupt 1 */
#define CR_HINT0	0x00000400	/* h/w interrupt 0 */
#define CR_HINT1	0x00000800	/* h/w interrupt 1 */
#define CR_HINT2	0x00001000	/* h/w interrupt 2 */
#define CR_HINT3	0x00002000	/* h/w interrupt 3 */
#define CR_HINT4	0x00004000	/* h/w interrupt 4 */
#define CR_HINT5	0x00008000	/* h/w interrupt 5 */

/* alternative interrupt pending bit naming */
#define CR_IP0		0x00000100
#define CR_IP1		0x00000200
#define CR_IP2		0x00000400
#define CR_IP3		0x00000800
#define CR_IP4		0x00001000
#define CR_IP5		0x00002000
#define CR_IP6		0x00004000
#define CR_IP7		0x00008000

#define CR_IMASK	0x0000ff00 	/* interrupt pending mask */
#define CR_XMASK	0x0000007c 	/* exception code mask */
#define CR_XCPT(x)	((x)<<2)


/*
 * R4650 Status Register 
 */
#define SR_IE		0x00000001 	/* interrupt enable */
#define SR_EXL		0x00000002	/* exception level */
#define SR_ERL		0x00000004	/* error level */

#define SR_UM		0x00000010	/* user mode */
#define SR_KSU_MASK	0x00000010	/* ksu mode mask */
#define SR_KSU_USER	0x00000010	/* user mode */
#define SR_KSU_KERN	0x00000000	/* kernel mode */

#define SR_UX		0x00000020	/* mips3 in user mode */

/* interrupt mask bits */
#define SR_SINT0	0x00000100	/* enable s/w interrupt 0 */
#define SR_SINT1	0x00000200	/* enable s/w interrupt 0 */
#define SR_HINT0	0x00000400	/* enable h/w interrupt 1 */
#define SR_HINT1	0x00000800	/* enable h/w interrupt 2 */
#define SR_HINT2	0x00001000	/* enable h/w interrupt 3 */
#define SR_HINT3	0x00002000	/* enable h/w interrupt 4 */
#define SR_HINT4	0x00004000	/* enable h/w interrupt 5 */
#define SR_HINT5	0x00008000	/* enable h/w interrupt 6 */

/* alternative interrupt mask naming */
#define SR_IM0		0x00000100
#define SR_IM1		0x00000200
#define SR_IM2		0x00000400
#define SR_IM3		0x00000800
#define SR_IM4		0x00001000
#define SR_IM5		0x00002000
#define SR_IM6		0x00004000
#define SR_IM7		0x00008000

#define SR_IMASK	0x0000ff00

/* diagnostic field */
#define SR_DE		0x00010000	/* disable cache/ecc errors */
#define SR_CE		0x00020000	/* use ecc register */
#define SR_CH		0x00040000 	/* cache hit indicator */
#define SR_SR		0x00100000	/* soft reset occurred */
#define SR_BEV		0x00400000	/* boot exception vectors */
#define SR_IL		0x00800000	/* icache lock */
#define SR_DL		0x01000000	/* dcache lock */

#define SR_RE		0x02000000	/* reverse endian (user mode) */
#define SR_FR		0x04000000	/* 64-bit fpu registers */

#define SR_CU0		0x10000000	/* coprocessor 0 enable */
#define SR_CU1		0x20000000	/* coprocessor 1 enable */
#define SR_CU2		0x40000000	/* coprocessor 2 enable */
#define SR_CU3		0x80000000	/* coprocessor 3 enable */


/*
 * Config Register 
 */
#define CFG_CM		0x80000000	/* Master-Checker mode */
#define CFG_ECMASK	0x70000000	/* System Clock Ratio */
#define CFG_ECSHIFT	28
#define CFG_EPMASK	0x0f000000	/* Transmit data pattern */
#define CFG_EPD		0x00000000	/* D */
#define CFG_EPDDX	0x01000000	/* DDX */
#define CFG_EPDDXX	0x02000000	/* DDXX */
#define CFG_EPDXDX	0x03000000	/* DXDX */
#define CFG_EPDDXXX	0x04000000	/* DDXXX */
#define CFG_EPDDXXXX	0x05000000	/* DDXXXX */
#define CFG_EPDXXDXX	0x06000000	/* DXXDXX */
#define CFG_EPDDXXXXX	0x07000000	/* DDXXXXX */
#define CFG_EPDXXXDXXX	0x08000000	/* DXXXDXXX */
#define CFG_SBMASK	0x00c00000	/* Secondary cache block size */
#define CFG_SBSHIFT	22
#define CFG_SB4		0x00000000	/* 4 words */
#define CFG_SB8		0x00400000	/* 8 words */
#define CFG_SB16	0x00800000	/* 16 words */
#define CFG_SB32	0x00c00000	/* 32 words */
#define CFG_SS		0x00200000	/* Split secondary cache */
#define CFG_SW		0x00100000	/* Secondary cache port width */
#define CFG_EWMASK	0x000c0000	/* System port width */
#define CFG_EWSHIFT	18
#define CFG_EW64	0x00000000	/* 64 bit */
#define CFG_EW32	0x00010000	/* 32 bit */
#define CFG_SC		0x00020000	/* Secondary cache absent */
#define CFG_SM		0x00010000	/* Dirty Shared mode disabled */
#define CFG_BE		0x00008000	/* Big Endian */
#define CFG_EM		0x00004000	/* ECC mode enable */
#define CFG_EB		0x00002000	/* Block ordering */
#define CFG_ICMASK	0x00000e00	/* Instruction cache size */
#define CFG_ICSHIFT	9
#define CFG_DCMASK	0x000001c0	/* Data cache size */
#define CFG_DCSHIFT	6
#define CFG_IB		0x00000020	/* Instruction cache block size */
#define CFG_DB		0x00000010	/* Data cache block size */
#define CFG_CU		0x00000008	/* Update on Store Conditional */
#define CFG_K0MASK	0x00000007	/* KSEG0 coherency (unused) */

/*
 * KSEG0 cache mode (not used)
 */
#define CFG_C_WTHRU_NOALLOC	0
#define CFG_C_WTHRU_ALLOC	1
#define CFG_C_UNCACHED		2
#define CFG_C_NONCOHERENT	3
#define CFG_C_WBACK		3

/*
 * Cache Algorithm field values
 */
#define CALG_WTHRU_NOALLOC	0
#define CALG_WTHRU_ALLOC	1
#define CALG_UNCACHED		2
#define CALG_WBACK		3

/* 
 * Primary Cache TagLo 
 */
#define TAG_PTAG_MASK           0xffffff00      /* Primary Tag */
#define TAG_PTAG_SHIFT          8
#define TAG_PSTATE_MASK         0x000000c0      /* Primary Cache State */
#define TAG_PSTATE_SHIFT        6
#define TAG_FIFO	        0x00000004      /* Primary Tag Parity */
#define TAG_PARITY	        0x00000001      /* Primary Tag Parity */

#define PSTATE_INVAL		0
#define PSTATE_SHARED		1
#define PSTATE_CLEAN_EXCL	2
#define PSTATE_DIRTY_EXCL	3


/*
 * CacheErr register
 */
#define CACHEERR_TYPE		0x80000000	/* reference type: 
						   0=Instr, 1=Data */
#define CACHEERR_LEVEL		0x40000000	/* cache level:
						   0=Primary, 1=Secondary */
#define CACHEERR_DATA		0x20000000	/* data field:
						   0=No error, 1=Error */
#define CACHEERR_TAG		0x10000000	/* tag field:
						   0=No error, 1=Error */
#define CACHEERR_REQ		0x08000000	/* request type:
						   0=Internal, 1=External */
#define CACHEERR_BUS		0x04000000	/* error on bus:
						   0=No, 1=Yes */
#define CACHEERR_BOTH		0x02000000	/* Data & Instruction error:
						   0=No, 1=Yes */
#define CACHEERR_STORE		0x01000000	/* Scache error on store miss :
						   0=No, 1=Yes */
#define CACHEERR_MP		0x00800000	/* Multiprocessor error :
						   0=No, 1=Yes */
#define CACHEERR_SIDX_MASK	0x003ffff8	/* PADDR(21..3) */
#define CACHEERR_SIDX_SHIFT		 3
#define CACHEERR_PIDX_MASK	0x00000007	/* VADDR(14..12) */
#define CACHEERR_PIDX_SHIFT		12


/*
 * Cache operations
 */
#define Index_Invalidate_I               0x0         /* 0       0 */
#define Index_Writeback_Inv_D            0x1         /* 0       1 */
#define Index_Invalidate_SI              0x2         /* 0       2 */
#define Index_Writeback_Inv_SD           0x3         /* 0       3 */
#define Index_Load_Tag_I                 0x4         /* 1       0 */
#define Index_Load_Tag_D                 0x5         /* 1       1 */
#define Index_Load_Tag_SI                0x6         /* 1       2 */
#define Index_Load_Tag_SD                0x7         /* 1       3 */
#define Index_Store_Tag_I                0x8         /* 2       0 */
#define Index_Store_Tag_D                0x9         /* 2       1 */
#define Index_Store_Tag_SI               0xA         /* 2       2 */
#define Index_Store_Tag_SD               0xB         /* 2       3 */
#define Create_Dirty_Exc_D               0xD         /* 3       1 */
#define Create_Dirty_Exc_SD              0xF         /* 3       3 */
#define Hit_Invalidate_I                 0x10        /* 4       0 */
#define Hit_Invalidate_D                 0x11        /* 4       1 */
#define Hit_Invalidate_SI                0x12        /* 4       2 */
#define Hit_Invalidate_SD                0x13        /* 4       3 */
#define Hit_Writeback_Inv_D              0x15        /* 5       1 */
#define Hit_Writeback_Inv_SD             0x17        /* 5       3 */
#define Fill_I                           0x14        /* 5       0 */
#define Hit_Writeback_D                  0x19        /* 6       1 */
#define Hit_Writeback_SD                 0x1B        /* 6       3 */
#define Hit_Writeback_I                  0x18        /* 6       0 */
#define Hit_Set_Virtual_SI               0x1E        /* 7       2 */
#define Hit_Set_Virtual_SD               0x1F        /* 7       3 */

/* IWatch Register */
#define IWATCH_VA	0xfffffffc
#define IWATCH_EN	0x00000001

/* DWatch Register */
#define DWATCH_VA	0xfffffff8
#define DWATCH_R	0x00000004
#define DWATCH_W	0x00000002

#ifdef __ASSEMBLER__
/* 
 * R4650 Coprocessor 0 register numbers 
 */
#define C0_IBASE	$0
#define C0_IBOUND	$1
#define C0_DBASE	$2
#define C0_DBOUND	$3
#define C0_BADVADDR 	$8
#define C0_VADDR 	$8
#define C0_COUNT 	$9
#define C0_COMPARE	$11
#define C0_STATUS	$12
#define C0_SR		$12
#define C0_CAUSE	$13
#define C0_CR		$13
#define C0_EPC 		$14
#define C0_PRID		$15
#define C0_CONFIG	$16
#define C0_CALG		$17
#define C0_IWATCH	$18
#define C0_DWATCH	$19
#define C0_ECC		$26
#define C0_CACHEERR	$27
#define C0_TAGLO	$28
#define C0_TAGHI	$29	/* not used, but for compat */
#define C0_ERRPC	$30

$ibase		=	$0
$ibound		=	$1
$dbase		=	$2
$dbound		=	$3
$vaddr 		=	$8
$count 		=	$9
$compare	=	$11
$sr		=	$12
$cr		=	$13
$epc 		=	$14
$prid		=	$15
$config		=	$16
$calg		=	$17
$iwatch		=	$18
$dwatch		=	$19
$ecc		=	$26
$cacheerr	=	$27
$taglo		=	$28
$errpc		=	$30

/* 
 * R4650 extra virtual memory regions 
 */
#define	KUSEG_BASE	0x00000000
#define	KSEG2_BASE	0xc0000000
#define KUSEG_SIZE	0x80000000
#define KSEG2_SIZE	0x40000000

/* 
 * Translate a physical address to KSEG2
 */
#define PA_TO_KVA2(pa)	((pa) | 0xc0000000)


#else

/*
 * Standard types
 */
typedef unsigned long		reg32_t;	/* a 32-bit register */
typedef unsigned long long	reg64_t;	/* a 64-bit register */
#if __mips >= 3 || __mips64
typedef unsigned long long	reg_t;
typedef signed long long	sreg_t;
#else
typedef unsigned long		reg_t;
typedef signed long		sreg_t;
#endif

/* 
 * R4650 Coprocessor 0 register numbers 
 */
#define C0_IBASE	0
#define C0_IBOUND	1
#define C0_DBASE	2
#define C0_DBOUND	3
#define C0_BADVADDR 	8
#define C0_VADDR 	8
#define C0_COUNT 	9
#define C0_COMPARE	11
#define C0_STATUS	12
#define C0_SR		12
#define C0_CAUSE	13
#define C0_CR		13
#define C0_EPC 		14
#define C0_PRID		15
#define C0_CONFIG	16
#define C0_CALG		17
#define C0_IWATCH	18
#define C0_DWATCH	19
#define C0_ECC		26
#define C0_CACHEERR	27
#define C0_TAGLO	28
#define C0_ERRPC	30

#define _mips_nop() \
  __asm__ __volatile ("%(nop%)" : :) 

#define _mips_sync() \
  __asm__ __volatile__ ("sync" : : : "memory")

#define _mips_wait() \
  __asm__ __volatile ("wait")

/* 
 * Define generic macros for accessing the R3000 coprocessor 0 registers.
 * Most apart from "set" return the original register value.
 */

#define _mips_mfc0(reg) \
({ \
  register reg32_t __r; \
  __asm__ __volatile ("mfc0 %0,$%1" \
		      : "=d" (__r) \
		      : "JK" (reg)); \
  __r; \
})

#define _mips_mtc0(reg, val) \
do { \
    __asm__ __volatile ("%(mtc0 %z0,$%1; nop; nop; nop%)" \
			: \
			: "dJ" ((reg32_t)(val)), "JK" (reg) \
			: "memory");\
} while (0)


/* R4650 IBase register */
#define r4650_getibase()	_mips_mfc0(0)
#define r4650_setibase(v)	_mips_mtc0(0,v)
#define r4650_xchibase(v)	_mips_mxc0(0,v)

/* R4650 IBound register */
#define r4650_getibound()	_mips_mfc0(1)
#define r4650_setibound(v)	_mips_mtc0(1,v)
#define r4650_xchibound(v)	_mips_mxc0(1,v)

/* R4650 DBase register */
#define r4650_getdbase()	_mips_mfc0(2)
#define r4650_setdbase(v)	_mips_mtc0(2,v)
#define r4650_xchdbase(v)	_mips_mxc0(2,v)

/* R4650 DBound register */
#define r4650_getdbound()	_mips_mfc0(3)
#define r4650_setdbound(v)	_mips_mtc0(3,v)
#define r4650_xchdbound(v)	_mips_mxc0(3,v)

/* R4650 CAlg register */
#define r4650_getcalg()		_mips_mfc0(17)
#define r4650_setcalg(v)	_mips_mtc0(17,v)
#define r4650_xchcalg(v)	_mips_mxc0(17,v)
#define r4650_biccalg(clr)	_mips_bcc0(17,clr)
#define r4650_biscalg(set)	_mips_bsc0(17,set)
#define r4650_bcsscalg(c,s)	_mips_bcsc0(17,c,s)

/* R4650 IWatch register */
#define r4650_getiwatch()	_mips_mfc0(18)
#define r4650_setiwatch(v)	_mips_mtc0(18,v)
#define r4650_xchiwatch(v)	_mips_mxc0(18,v)

/* R4650 DWatch register */
#define r4650_getdwatch()	_mips_mfc0(19)
#define r4650_setdwatch(v)	_mips_mtc0(19,v)
#define r4650_xchdwatch(v)	_mips_mxc0(19,v)

/* 
 * R4650 extra virtual memory regions
 */
#define KUSEG_BASE 	((void *)0x00000000)
#define KSEG2_BASE	((void *)0xc0000000)
#define KUSEG_SIZE	0x80000000u
#define KSEG2_SIZE	0x40000000u

/* 
 * Translate a kernel virtual address in KSEG0 or KSEG1 to a real
 * physical address and back.
 */
#define KVA2_TO_PA(v) 	((paddr_t)(v) & 0x3fffffff)
#define PA_TO_KVA2(pa)	((void *) ((pa) | 0xc0000000))

/* Test for KSEGS */
#define IS_KVA2(v)	(((unsigned)(v) >> 30) == 0x3)
#define IS_UVA(v)	((int)(v) >= 0)

#endif /* !ASSEMBLER */

#ifdef __cplusplus
}
#endif
#endif /* _MIPS_R4650_H_ */
