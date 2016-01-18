/*
 * Copyright (c) 1998-2006 MIPS Technologies, Inc.
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
 * rm7kc0.h : QED RM7000 coprocessor 0 definitions
 */


#ifndef _MIPS_RM7KC0_H_
#define _MIPS_RM7KC0_H_

#ifdef __cplusplus
extern "C" {
#endif

/* RM7000 MMU is R4000 compatible */
#assert mmu(r4k)
#include "mips/r4ktlb.h"

/*
 * RM7000 Exception Codes
 */
#define EXC_INTR	0	/* interrupt */
#define EXC_MOD		1	/* tlb modification */
#define EXC_TLBL	2	/* tlb miss (load/i-fetch) */
#define EXC_TLBS	3	/* tlb miss (store) */
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
#define EXC_FPE		15	/* floating point exception */
#define EXC_IWE		16	/* instruction watchpoint */
#define EXC_DWE		23	/* data watchpoint */

/*
 * RM7000 Cause Register 
 */
#define CR_BD		0x80000000	/* branch delay */
#define CR_CEMASK	0x30000000      /* coprocessor used */
#define CR_CESHIFT	28
#define CR_IV		0x01000000	/* interrupt vector enable */
#define CR_W1		0x02000000	/* watch 1 triggered */
#define CR_W2		0x04000000	/* watch 2 triggered */

/* interrupt pending bits */
#define CR_SINT0	0x00000100 	/* s/w interrupt 0 */
#define CR_SINT1	0x00000200	/* s/w interrupt 1 */
#define CR_HINT0	0x00000400	/* h/w interrupt 0 */
#define CR_HINT1	0x00000800	/* h/w interrupt 1 */
#define CR_HINT2	0x00001000	/* h/w interrupt 2 */
#define CR_HINT3	0x00002000	/* h/w interrupt 3 */
#define CR_HINT4	0x00004000	/* h/w interrupt 4 */
#define CR_HINT5	0x00008000	/* h/w interrupt 5 */
#define CR_HINT6	0x00010000	/* h/w interrupt 6 */
#define CR_HINT7	0x00020000	/* h/w interrupt 7 */
#define CR_HINT8	0x00040000	/* h/w interrupt 8 */
#define CR_HINT9	0x00080000	/* h/w interrupt 9 */
#define CR_HINT10	0x00100000	/* h/w interrupt 10 */
#define CR_HINT11	0x00200000	/* h/w interrupt 11 */
#define CR_HINT12	0x00400000	/* h/w interrupt 12 */
#define CR_HINT13	0x00800000	/* h/w interrupt 13 */

/* alternative interrupt pending bit naming */
#define CR_IP0		0x00000100
#define CR_IP1		0x00000200
#define CR_IP2		0x00000400
#define CR_IP3		0x00000800
#define CR_IP4		0x00001000
#define CR_IP5		0x00002000
#define CR_IP6		0x00004000
#define CR_IP7		0x00008000
#define CR_IP8		0x00010000
#define CR_IP9		0x00020000
#define CR_IP10		0x00040000
#define CR_IP11		0x00080000
#define CR_IP12		0x00100000
#define CR_IP13		0x00200000
#define CR_IP14		0x00400000
#define CR_IP15		0x00800000

#define CR_IMASK	0x00ffff00 	/* interrupt pending mask */
#define CR_XMASK	0x0000007c 	/* exception code mask */
#define CR_XCPT(x)	((x)<<2)


/*
 * RM7000 Status Register 
 */
#define SR_IE		0x00000001 	/* interrupt enable */
#define SR_EXL		0x00000002	/* exception level */
#define SR_ERL		0x00000004	/* error level */

#define SR_KSU_MASK	0x00000018	/* ksu mode mask */
#define SR_KSU_USER	0x00000010	/* user mode */
#define SR_KSU_SPVS	0x00000008	/* supervisor mode */
#define SR_KSU_KERN	0x00000000	/* kernel mode */

#define SR_UX		0x00000020	/* mips3 & xtlb in user mode */
#define SR_SX		0x00000040	/* mips3 & xtlb in supervisor mode */
#define SR_KX		0x00000080	/* xtlb in kernel mode */

/* interrupt mask bits */
#define SR_SINT0	0x00000100	/* enable s/w interrupt 0 */
#define SR_SINT1	0x00000200	/* enable s/w interrupt 1 */
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
#define SR_SR		0x00100000	/* soft reset occurred */
#define SR_BEV		0x00400000	/* boot exception vectors */

#define SR_RE		0x02000000	/* reverse endian (user mode) */
#define SR_FR		0x04000000	/* 64-bit fpu registers */
#define SR_CO		0x08000000	/* enable use cache flush */

#define SR_CU0		0x10000000	/* coprocessor 0 enable */
#define SR_CU1		0x20000000	/* coprocessor 1 enable */
#define SR_CU2		0x40000000	/* coprocessor 2 enable */
#define SR_XX		0x80000000	/* Mips IV ISA enable */


/*
 * RM7000 Config Register 
 */
#define CFG_SC		0x80000000	/* Secondary Cache Present */
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
#define CFG_SBMASK	0x00c00000	/* Scache block size */
#define CFG_SBSHIFT	22
#define CFG_PIMASK	0x00300000	/* Processor ID */
#define CFG_PISHIFT	20
#define CFG_EWMASK	0x000c0000
#define CFG_EW64	0x00000000
#define CFG_TC		0x00020000	/* Tertiary Cache Present */
#define CFG_CLK		0x00010000	/* Half-integer clock multiplier */
#define CFG_BE		0x00008000	/* Big Endian */
#define CFG_EM		0x00004000	/* ECC Mode */
#define CFG_EB		0x00002000	/* Block ordering */
#define CFG_TE		0x00001000	/* Tertiary Cache Enable */
#define CFG_ICMASK	0x00000e00	/* Instruction cache size */
#define CFG_ICSHIFT	9
#define CFG_DCMASK	0x000001c0	/* Data cache size */
#define CFG_DCSHIFT	6
#define CFG_IB		0x00000020	/* Instruction cache block size */
#define CFG_DB		0x00000010	/* Data cache block size */
#define CFG_SE		0x00000008
#define CFG_K0MASK	0x00000007	/* KSEG0 coherency algorithm */

/*
 * Primary cache mode
 */
#define CFG_C_WTHRU_NOALLOC	0
#define CFG_C_WTHRU_ALLOC	1
#define CFG_C_UNCACHED		2
#define CFG_C_NONCOHERENT	3
#define CFG_C_WBACK		3
#define CFG_C_UNCACHED_NOBLOCK	6
#define CFG_C_BYPASS		7

/*
 * RM7000A Info Register 
 */
#define INFO_TL		0x20000000	/* Large TLB: 64 entries */
#define INFO_BM		0x10000000	/* Burst Mode Scache RAMS */
#define INFO_DSMASK	0x0c000000	/* Drive Strength */
#define INFO_DSSHIFT	26
#define INFO_NP		0x02000000	/* Non-Pendant bus mode */
#define INFO_WPMASK	0x01800000	/* Write Protocol */
#define INFO_WPSHIFT	23
#define INFO_DWMASK	0x007e0000	/* Dcache ways/sets */
#define INFO_DWSHIFT	17
#define INFO_IWMASK	0x0001f800	/* Icache ways/sets */
#define INFO_IWSHIFT	11
#define INFO_SWMASK	0x000007e0	/* Scache ways/sets */
#define INFO_SWSHIFT	5
#define INFO_SSMASK	0x0000001e	/* Scache size */
#define INFO_SSSHIFT	1
#define INFO_AE		0x00000001	/* Atomic Enable */

/*
 * RM7000 TagLo register
 * Interpreted differently depending on cache type
 */

/* Primary Cache TagLo */
#define TAGLO_PREDEC_MASK	0xfff00000 	/* Icache predecode */
#define TAGLO_PREDEC_SHIFT	20	
#define TAGLO_PSTATE_MASK	0x000000c0 	/* Cache State */
#define TAGLO_PSTATE_SHIFT	6	

/* Secondary Cache TagLo */
#define TAGLO_SSTATE_MASK	0x000001c0 	/* Cache State */
#define TAGLO_SSTATE_SHIFT	6	

/* Tertiary Cache TagLo */
#define TAGLO_TSTATE_MASK	0x000001c0 	/* Cache State */
#define TAGLO_TSTATE_SHIFT	6

/* Common TagLo bits */
#define TAGLO_SP		0x00000020 	/* State Parity */
#define TAGLO_B			0x00000008 	/* Bypass */
#define TAGLO_L			0x00000004 	/* Locked */
#define TAGLO_F			0x00000002 	/* Fifo bit */
#define TAGLO_P			0x00000001 	/* SP,B,P,L Parity */

/* another way */
#define TAGLO_SPARITY_MASK	0x00000020 	/* State Parity */
#define TAGLO_SPARITY_SHIFT	5
#define TAGLO_BYPASS_MASK	0x00000008 	/* Bypass */
#define TAGLO_BYPASS_SHIFT	3
#define TAGLO_LOCK_MASK		0x00000004 	/* Locked */
#define TAGLO_LOCK_SHIFT	2
#define TAGLO_FIFO_MASK		0x00000002 	/* Fifo bit */
#define TAGLO_FIFO_SHIFT	1
#define TAGLO_PARITY_MASK	0x00000001 	/* SP,B,P,L Parity */
#define TAGLO_PARITY_SHIFT	0

/* State values for primary cache */
#define TAGLO_PSTATE_INVAL	0
#define TAGLO_PSTATE_PENDING	1
#define TAGLO_PSTATE_IVALID	2	 	/* InstrValid */
#define TAGLO_PSTATE_DVALID	3	 	/* DataValid */

/* State values for secondary cache */
#define TAGLO_SSTATE_INVAL	0
#define TAGLO_SSTATE_CLEAN	4
#define TAGLO_SSTATE_DIRTY	5
#define TAGLO_SSTATE_PENDING	6
#define TAGLO_SSTATE_DIRTY_DC	7

/* State values for tertiary cache */
#define TAGLO_TSTATE_INVAL	0
#define TAGLO_TSTATE_VALID	4

/*
 * RM7000 TagHi register
 */
#define TAGHI_PTAG_MASK 	0xffffff00
#define TAGHI_STAG_MASK 	0xfffff000
#define TAGHI_TTAG_MASK 	0xffff8000
#define TAGHI_ADDRTOIDX(addr)	((unsigned)(addr) >> 4)
#define TAGHI_IDXTOADDR(idx)	((unsigned)(addr) << 4)

/*
 * RM7000 ECC register
 */
#define ECC_SS			0x10000000 	/* Set Select */
#define ECC_I			0x08000000 	/* Enable Icache locking */
#define ECC_D			0x04000000 	/* Enable Dcache locking */
#define ECC_S			0x02000000 	/* Enable Scache locking */
#define ECC_PARMASK		0x000000ff 	/* Parity bits */

/*
 * RM7000 CacheErr register
 */
#define CACHEERR_ER		0x80000000
#define CACHEERR_TYPE		0x80000000	/* reference type: 
						   0=Instr, 1=Data */
#define CACHEERR_EC		0x40000000
#define CACHEERR_LEVEL		0x40000000	/* cache level:
						   0=Primary, 1=Secondary */

#define CACHEERR_ED		0x20000000
#define CACHEERR_DATA		0x20000000	/* data field:
						   0=No error, 1=Error */

#define CACHEERR_ET		0x10000000
#define CACHEERR_TAG		0x10000000	/* tag field:
						   0=No error, 1=Error */
#define CACHEERR_EE		0x04000000
#define CACHEERR_BUS		0x04000000	/* error on bus:
						   0=No, 1=Yes */

#define CACHEERR_E0		0x00800000	/* Physaddr in DErrAddr1 */

#define CACHEERR_E1		0x00400000	/* Physaddr in DErrAddr2 */

#define CACHEERR_IDX		0x003ffff8	/* Physaddr 21:3 */

/* RM7000 Watch1 and Watch2 registers */
#define WATCH_ST	0x8000000000000000LL	/* Watch Stores */
#define WATCH_LD	0x4000000000000000LL	/* Watch Loads */
#define WATCH_IN	0x2000000000000000LL	/* Watch Ifetch */
#define WATCH_PA	0x0000000ffffffffcLL 	/* Phyaddr 35:2 */

/* RM7000 WatchMask register */
#define WATCHMASK_MASK	0xfffffffc 		/* Address mask */
#define WATCHMASK_W2	0x00000002 		/* Apply to Watch2 */
#define WATCHMASK_W1	0x00000001 		/* Apply to Watch1 */

/* RM7000 ECC register */
#define ECC_SS		0x10000000		/* Set Select */
#define ECC_I		0x08000000		/* I-cache locking */
#define ECC_D		0x04000000		/* D-cache locking */
#define ECC_S		0x02000000		/* S-cache locking */
#define ECC_PAR		0x000000ff		/* Cache parity */

/* RM7000 PerfCtrl register */
#define PERFCTRL_CE	0x00000400 		/* Count Enable */
#define PERFCTRL_UM	0x00000200 		/* Count in User Mode */
#define PERFCTRL_KM	0x00000100 		/* Count in Kernel Mode */
#define PERFCTRL_CSF	0x0000001f 		/* Counter Select */

/* RM7000 PerfCtrl counter select */
#define PERFCTRL_CS_PCLOCK	0x00		/* Clock cycles */
#define PERFCTRL_CS_TOTAL_ISSUE	0x01		/* Total insns issued */
#define PERFCTRL_CS_FP_ISSUE	0x02		/* FP insns issued */
#define PERFCTRL_CS_INT_ISSUE	0x03		/* Int insns issued */
#define PERFCTRL_CS_LOAD	0x04		/* Load insns issued */
#define PERFCTRL_CS_STORE	0x05		/* Store insns issued */
#define PERFCTRL_CS_DUAL_ISSUE	0x06		/* Dual issued pairs */
#define PERFCTRL_CS_BR_PREFETCH	0x07		/* Branch prefetches */
#define PERFCTRL_CS_TCMISS	0x08		/* T-cache misses */
#define PERFCTRL_CS_STALL	0x09		/* Stall cycles */
#define PERFCTRL_CS_SCMISS	0x0a		/* S-cache misses */
#define PERFCTRL_CS_ICMISS	0x0b		/* I-cache misses */
#define PERFCTRL_CS_DCMISS	0x0c		/* D-cache misses */
#define PERFCTRL_CS_DTLBMISS	0x0d		/* DTLB misses */
#define PERFCTRL_CS_ITLBMISS	0x0e		/* ITLB misses */
#define PERFCTRL_CS_IJTLBMISS	0x0f		/* JTLB insn misses */
#define PERFCTRL_CS_DJTLBMISS	0x10		/* JTLB data misses */
#define PERFCTRL_CS_BR_TAKEN	0x11		/* Branches taken */
#define PERFCTRL_CS_BR_ISSUE	0x12		/* Branches issued */
#if 1	/* errata */	
#define PERFCTRL_CS_DC_WBACK	0x13		/* D-cache writebacks */
#else
#define PERFCTRL_CS_SC_WBACK	0x13		/* S-cache writebacks */
#define PERFCTRL_CS_DC_WBACK	0x14		/* D-cache writebacks */
#endif
#define PERFCTRL_CS_DC_STALL	0x15		/* D-cache miss stalls */
#define PERFCTRL_CS_MISS	0x16		/* Cache misses */
#define PERFCTRL_CS_FPU_STALL	0x17		/* FPU stalls */
/* Rev2.0 only from here */
#define PERFCTRL_CS_MULT_SLIP	0x18		/* Multiplier slip cycles */
#define PERFCTRL_CS_CP0_SLIP	0x19		/* Coprocessor 0 slip cycles */
#define PERFCTRL_CS_NBLD_SLIP	0x1a		/* NB-load slip cycles */
#define PERFCTRL_CS_WB_STALL	0x1b		/* Write buffer full stalls */
#define PERFCTRL_CS_CACHE_STALL	0x1c		/* Cache insn stalls */
#define PERFCTRL_CS_MULT_STALL	0x1d		/* Multuplier stalls */
#define PERFCTRL_CS_NBLD_STALL	0x1e		/* NB-load stalls */

/*
 * RM7000 Cache operations
 */
#define Index_Invalidate_I               0x00        /* 0       0 */
#define Index_Writeback_Inv_D            0x01        /* 0       1 */
#define Flash_Invalidate_T		 0x02        /* 0       2 */
#define Index_Writeback_Inv_S            0x03        /* 0       3 */
/*----*/
#define Index_Load_Tag_I                 0x04        /* 1       0 */
#define Index_Load_Tag_D                 0x05        /* 1       1 */
#define Index_Load_Tag_T                 0x06        /* 1       2 */
#define Index_Load_Tag_S                 0x07        /* 1       3 */
/*----*/
#define Index_Store_Tag_I                0x08        /* 2       0 */
#define Index_Store_Tag_D                0x09        /* 2       1 */
#define Index_Store_Tag_T                0x0A        /* 2       2 */
#define Index_Store_Tag_S                0x0B        /* 2       3 */
/*----*/
#define Create_Dirty_Exc_D               0x0D        /* 3       1 */
/*----*/
#define Hit_Invalidate_I                 0x10        /* 4       0 */
#define Hit_Invalidate_D                 0x11        /* 4       1 */
#define Hit_Invalidate_S                 0x13        /* 4       3 */
/*----*/
#define Fill_I                           0x14        /* 5       0 */
#define Hit_Writeback_Inv_D              0x15        /* 5       1 */
#define Page_Invalidate_T                0x16        /* 5       2 */
#define Hit_Writeback_Inv_S              0x17        /* 5       3 */
/*----*/
#define Hit_Writeback_I                  0x18        /* 6       0 */
#define Hit_Writeback_D                  0x19        /* 6       1 */
#define Hit_Writeback_S                  0x1B        /* 6       3 */


#ifdef __ASSEMBLER__
/* 
 * RM7000 Coprocessor 0 register numbers 
 */

/* data registers, access via mfc0/mtc0 */
#define C0_INDEX	$0
#define C0_INX		$0
#define C0_RANDOM	$1
#define C0_RAND		$1
#define C0_ENTRYLO0	$2
#define C0_TLBLO0	$2
#define C0_ENTRYLO1	$3
#define C0_TLBLO1	$3
#define C0_CONTEXT	$4
#define C0_CTXT		$4
#define C0_PAGEMASK	$5
#define C0_WIRED	$6
#define C0_INFO		$7
#define C0_BADVADDR 	$8
#define C0_VADDR 	$8
#define C0_COUNT 	$9
#define C0_ENTRYHI	$10
#define C0_TLBHI	$10
#define C0_COMPARE	$11
#define C0_STATUS	$12
#define C0_SR		$12
#define C0_CAUSE	$13
#define C0_CR		$13
#define C0_EPC 		$14
#define C0_PRID		$15
#define C0_CONFIG	$16
#define C0_LLADDR	$17
#define C0_WATCH1	$18
#define C0_WATCH2	$19
#define C0_PERFCTRL	$22
#define C0_WATCHMASK	$24
#define C0_PERFCOUNT	$25
#define C0_ECC		$26
#define C0_CACHEERR	$27
#define C0_TAGLO	$28
#define C0_TAGHI	$29
#define C0_ERRPC	$30

/* control registers, access via cfc0/ctc0 */
#define C0C_IPLLO	$18
#define C0C_IPLHI	$19
#define C0C_ICR		$20
#define C0C_DERRADDR1	$26
#define C0C_DERRADDR2	$27

$index		=	$0
$random		=	$1
$entrylo0	=	$2
$entrylo1	=	$3
$context	=	$4
$pagemask	=	$5
$wired		=	$6
$info		=	$7
$vaddr 		=	$8
$count 		=	$9
$entryhi	=	$10
$compare	=	$11
$sr		=	$12
$cr		=	$13
$epc 		=	$14
$prid		=	$15
$config		=	$16
$lladdr		=	$17
$watch1		=	$18
$watch2		=	$19
$perfctrl	=	$22
$watchmask	=	$24
$perfcount	=	$25
$ecc		=	$26
$cacheerr	=	$27
$taglo		=	$28
$taghi		=	$29
$errpc		=	$30

$c_ipllo	=	$18
$c_iplhi	=	$19
$c_icr		=	$20
$c_derraddr1	=	$26
$c_derraddr2	=	$27

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
 * RM7000 Coprocessor 0 register numbers 
 */
#define C0_INDEX	0
#define C0_INX		0
#define C0_RANDOM	1
#define C0_RAND		1
#define C0_ENTRYLO0	2
#define C0_TLBLO0	2
#define C0_ENTRYLO1	3
#define C0_TLBLO1	3
#define C0_CONTEXT	4
#define C0_CTXT		4
#define C0_PAGEMASK	5
#define C0_WIRED	6
#define C0_INFO		7
#define C0_BADVADDR 	8
#define C0_VADDR 	8
#define C0_COUNT 	9
#define C0_ENTRYHI	10
#define C0_TLBHI	10
#define C0_COMPARE	11
#define C0_STATUS	12
#define C0_SR		12
#define C0_CAUSE	13
#define C0_CR		13
#define C0_EPC 		14
#define C0_PRID		15
#define C0_CONFIG	16
#define C0_LLADDR	17
#define C0_WATCH1	18
#define C0_WATCH2	19
#define C0_PERFCTRL	22
#define C0_WATCHMASK	24
#define C0_PERFCOUNT	25
#define C0_ECC		26
#define C0_CACHEERR	27
#define C0_TAGLO	28
#define C0_TAGHI	29
#define C0_ERRPC	30

/* control registers, access via cfc0/ctc0 */
#define C0C_IPLLO	18
#define C0C_IPLHI	19
#define C0C_ICR		20
#define C0C_DERRADDR1	26
#define C0C_DERRADDR2	27

#define _mips_nop() \
  __asm__ __volatile ("%(nop%)" : :) 

#define _mips_sync() __asm__ __volatile__ ("sync" : : : "memory")

#define _mips_wait() \
  __asm__ __volatile ("wait")

/* 
 * Define generic macros for accessing the coprocessor 0 registers.
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
    __asm__ __volatile ("%(mtc0 %z0,$%1%)" \
			: \
			: "dJ" ((reg32_t)(val)), "JK" (reg) \
			: "memory");\
} while (0)


#if __mips64
#define _mips_dmfc0(reg) \
({ \
  register reg64_t __r; \
  __asm__ __volatile ("dmfc0 %0,$%1" \
		      : "=d" (__r) \
		      : "JK" (reg)); \
  __r; \
})

#define _mips_dmtc0(reg, val) \
do { \
    __asm__ __volatile ("%(dmtc0 %z0,$%1%)" \
			: \
			: "dJ" ((reg64_t)(val)), "JK" (reg) \
			: "memory");\
} while (0)

#else
/* handle registers in two parts */
#define _mips_dmfc0(reg) \
({ \
  register reg64_t __r, __v; \
  __asm__ __volatile ("dmfc0 %0,$%1" \
		      : "=d" (__r) \
		      : "JK" (reg)); \
  __asm__ ("dsll %L0,%1,32; dsra %L0,%L0,32; dsra %M0,%1,32" \
	    : "=&d" (__v) \
	    : "d" (__r)); \
  __v; \
})

#define _mips_dmtc0(reg, val) \
do { \
    register reg64_t __v = (val), __r; \
    register reg32_t __t; \
    __asm__ ("dsll %0,%M2,32; dsll %1,%L2,32; dsrl %1,32; or %0,%1" \
	    : "=&d" (__r), "=&d" (__t) \
	    : "d" (__v)); \
    __asm__ __volatile ("%(dmtc0 %z0,$%1%)" \
			: \
			: "dJ" (__r), "JK" (reg) \
			: "memory");\
} while (0)

#endif

/* 
 * Define cpu-specific macros for accessing new RM7000 CP0 registers.
 */

#define _rm7k_cfc0(reg) \
({ \
  register reg32_t __r; \
  __asm__ __volatile ("cfc0 %0,$%1" \
		      : "=d" (__r) \
      		      : "JK" (reg)); \
  __r; \
})

#define _rm7k_ctc0(reg, val) \
do { \
    __asm__ __volatile ("%(ctc0 %z0,$%1%)" \
			: \
			: "dJ" ((reg32_t)(val)), "JK" (reg) \
			: "memory");\
} while (0)

#define _rm7k_cxc0(reg, val) \
({ \
    register reg32_t __o; \
    __o = _rm7k_cfc0 (reg); \
    _rm7k_ctc0 (reg, val); \
    __o; \
})

#define _rm7k_csc0(reg, set) \
({ \
    register reg32_t __o; \
    __o = _rm7k_cfc0 (reg); \
    _rm7k_ctc0 (reg, __o | (set)); \
    __o; \
})

#define _rm7k_ccc0(reg, clr) \
({ \
    register reg32_t __o; \
    __o = _rm7k_cfc0 (reg); \
    _rm7k_ctc0 (reg, __o & ~(clr)); \
    __o; \
})

#define _rm7k_ccsc0(reg, clr, set) \
({ \
    register reg32_t __o; \
    __o = _rm7k_cfc0 (reg); \
    _rm7k_ctc0 (reg, (__o & ~(clr)) | (set)); \
    __o; \
})

/* RM7000A Info register */
#define rm7k_getinfo()		_mips_mfc0(7)
#define rm7k_setinfo(v)		_mips_mtc0(7,v)

/* RM7000 PerfCtrl register */
#define rm7k_getperfctrl()	_mips_mfc0(22)
#define rm7k_setperfctrl(v)	_mips_mtc0(22,v)
#define rm7k_xchperfctrl(v)	_mips_mxc0(22,v)

/* RM7000 WatchMask register */
#define rm7k_getwatch1()	_mips_dmfc0(18)
#define rm7k_setwatch1(v)	_mips_dmtc0(18,v)

/* RM7000 WatchMask register */
#define rm7k_getwatch2()	_mips_dmfc0(19)
#define rm7k_setwatch2(v)	_mips_dmtc0(19,v)

/* RM7000 WatchMask register */
#define rm7k_getwatchmask()	_mips_mfc0(24)
#define rm7k_setwatchmask(v)	_mips_mtc0(24,v)
#define rm7k_xchwatchmask(v)	_mips_mxc0(24,v)

/* RM7000 PerfCount register */
#define rm7k_getperfcount()	_mips_mfc0(25)
#define rm7k_setperfcount(v)	_mips_mtc0(25,v)
#define rm7k_xchperfcount(v)	_mips_mxc0(25,v)

/* RM7000 IPLLo register */
#define rm7k_getipllo()		_rm7k_cfc0(18)
#define rm7k_setipllo(v)	_rm7k_ctc0(18,v)
#define rm7k_xchipllo(v)	_rm7k_cxc0(18,v)
#define rm7k_bcsipllo(c,s)	_rm7k_ccsc0(18,c,s)

/* RM7000 IPLHi register */
#define rm7k_getiplhi()		_rm7k_cfc0(19)
#define rm7k_setiplhi(v)	_rm7k_ctc0(19,v)
#define rm7k_xchiplhi(v)	_rm7k_cxc0(19,v)
#define rm7k_bcsiplhi(c,s)	_rm7k_ccsc0(19,c,s)

/* RM7000 IntCtrl register (NOTE they are NOT atomic operations) */
#define rm7k_geticr()		_rm7k_cfc0(20)
#define rm7k_seticr(v)		_rm7k_ctc0(20,v)
#define rm7k_xchicr(v)		_rm7k_cxc0(20,v)
#define rm7k_bicicr(clr)	_rm7k_ccc0(20,clr)
#define rm7k_bisicr(set)	_rm7k_csc0(20,set)
#define rm7k_bcsicr(c,s)	_rm7k_ccsc0(20,c,s)

/* RM7000 DerrAddr1 */
#define rm7k_getderraddr1()	_rm7k_cfc0(26)

/* RM7000 DerrAddr1 */
#define rm7k_getderraddr2()	_rm7k_cfc0(27)

#endif /* !ASSEMBLER */

#ifdef __cplusplus
}
#endif
#endif /* _MIPS_RM7KC0_H_ */
