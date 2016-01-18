/*
 * Copyright (c) 1998-2003 MIPS Technologies, Inc.
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
 * lsi/cw400x.h : SDE LSI CoreWare 400x definitions
 */


#ifndef _MIPS_CW400X_H_
#define _MIPS_CW400X_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The cw400x core is essentially an R3000
 * So far, none of them have a TLB
 */
#if !#mmu(r3k) && !#mmu(r4k) && !#mmu(cw10)
#assert mmu(no)
#endif
#include "mips/r3kc0.h"

/*
 * Exception Codes
 */
#undef	EXC_RESD
#define EXC_TR		0xd	  /* trap */                 

/*
 * Status Register 
 */

/* diagnostic field */
#undef	SR_ISC
#undef	SR_SWC
#undef	SR_PZ
#undef	SR_CM
#undef	SR_PE

#undef	SR_RE


/* System configuration module */
#define BSYS_BASE	0xbfff0000	/* system configuration */
#define BSYS_SCR	0xbfff0000	/* system configuration */
#ifndef __ASSEMBLER__
struct _bsys_module {
    unsigned int scr;			/* system configuration register */
};
#endif

#define SCR_TLBEN	(1<<31)		/* tlb enable */
#define	SCR_W		(1<<30)		/* write buffer enable */
#define SCR_DSNOOP	(1<<29)		/* D-snoop enable */
#define SCR_ISNOOP	(1<<28)		/* I-snoop enable */
#define SCR_FBE		(1<<24)		/* fast bus enable */
#define SCR_CPC3EN	(1<<19) 	/* connect Cpc3 to int */
#define SCR_CPC2EN	(1<<18)		/* connect Cpc2 to int */
#define SCR_CPC1EN	(1<<17) 	/* connect Cpc1 to int */
#define SCR_CPC0EN	(1<<16) 	/* connect Cpc0 to int */
#define SCR_E		(1<<13)		/* Data error */
#define SCR_PS_SHIFT	10
#define SCR_PS_MASK	(7<<SCR_PS_SHIFT)
#define SCR_PS_16	(0<<SCR_PS_SHIFT)	/* page size 16 words */
#define SCR_PS_32	(1<<SCR_PS_SHIFT)	/* page size 32 words */
#define SCR_PS_64	(2<<SCR_PS_SHIFT)	/* page size 64 words */
#define SCR_PS_128	(3<<SCR_PS_SHIFT)	/* page size 128 words */
#define SCR_PS_256	(4<<SCR_PS_SHIFT)	/* page size 256 words */
#define SCR_PS_512	(5<<SCR_PS_SHIFT)	/* page size 512 words */
#define SCR_PS_1024	(6<<SCR_PS_SHIFT)	/* page size 1024 words */
#define SCR_PS_2048	(7<<SCR_PS_SHIFT)	/* page size 2048 words */
#define SCR_CM_SHIFT	8
#define SCR_CM_MASK	(3<<SCR_CM_SHIFT)
#define SCR_CM_NORMAL	(0<<SCR_CM_SHIFT)
#define SCR_CM_IDATA	(1<<SCR_CM_SHIFT)
#define SCR_CM_ITAG	(2<<SCR_CM_SHIFT)
#define SCR_CM_DTAG	(3<<SCR_CM_SHIFT)
#define	SCR_R		(1<<7)		/* read priority */
#define SCR_DRS_SHIFT	5
#define SCR_DRS_MASK	(3<<SCR_DRS_SHIFT)
#define SCR_DRS_1	(0<<SCR_DRS_SHIFT)
#define SCR_DRS_2	(1<<SCR_DRS_SHIFT)
#define SCR_DRS_4	(2<<SCR_DRS_SHIFT)
#define SCR_DRS_8	(3<<SCR_DRS_SHIFT)
#define SCR_D		(1<<4)
#define SCR_IRS_SHIFT	2
#define SCR_IRS_MASK	(3<<SCR_IRS_SHIFT)
#define SCR_IRS_1	(0<<SCR_IRS_SHIFT)
#define SCR_IRS_2	(1<<SCR_IRS_SHIFT)
#define SCR_IRS_4	(2<<SCR_IRS_SHIFT)
#define SCR_IRS_8	(3<<SCR_IRS_SHIFT)
#define SCR_1E		(1<<1)
#define SCR_IE		(1<<0)

/* Optional timer module */
#define TMR_BASE	0xbfff0100	/* timer base */
#define TMR_TIC0	0xbfff0100	/* timer 0 initial count */
#define TMR_TCC0	0xbfff0104	/* timer 0 counter	 */
#define TMR_TIC1	0xbfff0108	/* timer 1 initial count */
#define TMR_TCC1	0xbfff010c	/* timer 1 counter	 */
#define TMR_TMODE	0xbfff0110	/* timer mode		 */
#define TMR_TSTAT	0xbfff0114	/* timer interrupt status*/

#ifndef __ASSEMBLER__
struct _timer_module {
    unsigned int tic0;		/* timer 0 initial count */
    unsigned int tcc0;		/* timer 0 counter	 */
    unsigned int tic1;		/* timer 1 initial count */
    unsigned int tcc1;		/* timer 1 counter	 */
    unsigned int tmode;		/* timer mode		 */
    unsigned int tstat;		/* timer interrupt status*/
};
#endif

/* Timer mode bits */
#define TMODE_DOG1	0x400	/* timer 1 watchpoint mode */
#define TMODE_PULSE1	0x200	/* timer 1 pulse mode */
#define TMODE_EN1	0x100	/* timer 1 enable */
#define TMODE_PULSE0	0x002	/* timer 0 pulse mode */
#define TMODE_EN0	0x001	/* timer 0 enable */

/* Timer ISR bits */
#define TSTAT_INT0	0x2	/* timer 0 interrupt pending */
#define TSTAT_IEN0	0x1	/* timer 0 interrupt enable */

#ifdef __cplusplus
}
#endif
#endif /* _MIPS_CW400X_H_*/

