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
 * r3kc0.h : SDE R3000 coprocessor 0 definitions
 */


#ifndef _MIPS_R3KC0_H_
#define _MIPS_R3KC0_H_
#ifdef __cplusplus
extern "C" {
#endif

#if #mmu(no)
#include "mips/notlb.h"
#else
#assert mmu(r3k)
#include "mips/r3ktlb.h"
#endif

/*
 * R3000 Exception Codes
 */
#define EXC_INTR	0x0       /* interrupt */                        
#define EXC_MOD		0x1       /* tlb modification */                 
#define EXC_TLBL	0x2       /* tlb miss (load/i-fetch) */          
#define EXC_TLBS	0x3       /* tlb miss (store) */                 
#define EXC_ADEL	0x4       /* address error (load/i-fetch) */     
#define EXC_ADES	0x5       /* address error (store) */            
#define EXC_IBE		0x6       /* bus error (i-fetch) */              
#define EXC_DBE		0x7       /* data bus error (load/store) */      
#define EXC_SYS		0x8       /* system call */                      
#define EXC_BP		0x9       /* breakpoint */                       
#define EXC_RI		0xa       /* reserved instruction */             
#define EXC_CPU		0xb       /* coprocessor unusable */             
#define EXC_OVF		0xc       /* integer overflow */                 
#define EXC_RESD	0xd
#define EXC_RESE	0xe
#define EXC_RESF	0xf


/*
 * R3000 Cause Register 
 */
#define CR_BD		0x80000000      /* branch delay */   
#define CR_CEMASK	0x30000000      /* coprocessor used */
#define CR_CESHIFT	28

/* interrupt pending bits */	                             
#define CR_SINT0	0x00000100      /* s/w interrupt 0 */
#define CR_SINT1	0x00000200      /* s/w interrupt 1 */
#define CR_HINT0	0x00000400      /* h/w interrupt 0 */
#define CR_HINT1	0x00000800      /* h/w interrupt 1 */
#define CR_HINT2	0x00001000      /* h/w interrupt 2 */
#define CR_HINT3	0x00002000      /* h/w interrupt 3 */
#define CR_HINT4	0x00004000      /* h/w interrupt 4 */
#define CR_HINT5	0x00008000      /* h/w interrupt 5 */

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
 * R3000 Status Register 
 */
#define SR_IEC		0x00000001	/* interrupt enable current */
#define SR_KUC		0x00000002	/* kernel mode current */

#define SR_IEP		0x00000004	/* interrupt enable prev */
#define SR_KUP		0x00000008	/* kernel mode prev */

#define SR_IEO		0x00000010	/* interrupt enable old */
#define SR_KUO		0x00000020	/* kernel mode old */

#define SR_IE		SR_IEC		/* generic alias for int enable */

#define SR_SINT0	0x00000100      /* enable s/w interrupt 0 */
#define SR_SINT1	0x00000200      /* enable s/w interrupt 0 */
#define SR_HINT0	0x00000400      /* enable h/w interrupt 1 */
#define SR_HINT1	0x00000800      /* enable h/w interrupt 2 */
#define SR_HINT2	0x00001000      /* enable h/w interrupt 3 */
#define SR_HINT3	0x00002000      /* enable h/w interrupt 4 */
#define SR_HINT4	0x00004000      /* enable h/w interrupt 5 */
#define SR_HINT5	0x00008000      /* enable h/w interrupt 6 */

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
#define SR_ISC		0x00010000	/* isolate caches */
#define SR_SWC		0x00020000	/* swap caches */
#define SR_PZ		0x00040000	/* cache parity zero */
#define SR_CM		0x00080000	/* cache miss */
#define SR_PE		0x00100000	/* cache parity error */
#define SR_TS		0x00200000	/* tlb shutdown */
#define SR_BEV		0x00400000	/* boot exception vectors */

#define SR_RE		0x02000000	/* reverse endian (user mode) */

#define SR_CU0		0x10000000      /* coprocessor 0 enable */
#define SR_CU1		0x20000000      /* coprocessor 1 enable */
#define SR_CU2		0x40000000      /* coprocessor 2 enable */
#define SR_CU3		0x80000000      /* coprocessor 3 enable */

#ifndef ROM_BASE
#define ROM_BASE	0xbfc00000	/* standard ROM base address */
#endif


#ifdef __ASSEMBLER__
#if !#mmu(no)
#define C0_INDEX	$0
#define C0_INX		$0
#define C0_RANDOM	$1
#define C0_RAND		$1
#define C0_ENTRYLO	$2
#define C0_TLBLO	$2
#define C0_CONTEXT	$4
#define C0_CTXT		$4
#define C0_ENTRYHI	$10
#define C0_TLBHI	$10
#endif /* !#mmu(no) */
#define C0_BADVADDR 	$8
#define C0_VADDR 	$8
#define C0_STATUS	$12
#define C0_SR		$12
#define C0_CAUSE	$13
#define C0_CR		$13
#define C0_EPC 		$14
#define C0_PRID		$15

#if !#mmu(no)
$index		=	$0
$random		=	$1
$entrylo	=	$2
$context	=	$4
$entryhi	=	$10
#endif /* !#mmu(no) */
$vaddr 		=	$8
$sr		=	$12
$cr		=	$13
$epc 		=	$14
$prid		=	$15

#else

/*
 * Standard types
 */
typedef unsigned long	reg32_t;	/* a 32-bit register */
typedef unsigned long	reg_t;		/* a register */
typedef signed long	sreg_t;		/* a signed register */

#if !#mmu(no)
#define C0_INDEX	0
#define C0_INX		0
#define C0_RANDOM	1
#define C0_RAND		1
#define C0_ENTRYLO	2
#define C0_TLBLO	2
#define C0_CONTEXT	4
#define C0_CTXT		4
#define C0_ENTRYHI	10
#define C0_TLBHI	10
#endif /* !#mmu(no) */
#define C0_BADVADDR 	8
#define C0_VADDR 	8
#define C0_STATUS	12
#define C0_SR		12
#define C0_CAUSE	13
#define C0_CR		13
#define C0_EPC 		14
#define C0_PRID		15

/* 
 * Define generic macros for accessing the R3000 coprocessor 0 registers.
 */

#define _mips_nop() \
  __asm__ __volatile ("%(nop%)" : :) 

#define _mips_sync() \
  (void)0

#if ! __mips16 || __force_mips16_asm

# define _mips_mfc0(reg) \
({ \
  register reg_t __r; \
  __asm__ __volatile ("mfc0 %0,$%1" \
		      : "=d" (__r) \
      		      : "JK" (reg)); \
  __r; \
})

#define _mips_mtc0(reg, val) \
do { \
    __asm__ __volatile ("%(mtc0 %z0,$%1; nop; nop%)" \
			: \
			: "dJ" ((reg32_t)(val)), "JK" (reg) \
			: "memory"); \
} while (0)

#else

#define _mips_mfc0(rn	) 	_mips_xxc0 ((rn) + 0, 0, 0)
#define _mips_mtc0(rn, v)	(void) _mips_xxc0 ((rn) + 0, ~0, v)

#endif /* !__mips16 */

#ifdef SDE11_COMPAT
/* The following are only for backwards compatibility with SDE 1.1 */
#define r3k_icsize	mips_icache_size
#define r3k_dcsize	mips_dcache_size
#define r3k_cinit	mips_init_cache
#define r3k_cinval	mips_clean_cache
#define r3k_icinval 	mips_clean_icache
#define r3k_dcinval 	mips_clean_dcache
#endif

#endif /* !ASSEMBLER */

#ifdef __cplusplus
}
#endif
#endif /* _MIPS_R3KC0_H_*/
