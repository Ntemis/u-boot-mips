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
 * r3081.h: IDT R3081 configuration register, and functions to access it.
 */


#ifndef _MIPS_R3081_H_
#define _MIPS_R3081_H_

/* generic R3000 definitions */
#include "mips/r3kc0.h"

#define CFG_LOCK	0x80000000	/* lock register */
#define CFG_SLOWBUS	0x40000000	/* slow external bus */
#define CFG_DBREFILL	0x20000000	/* data bus refill: 1/4 words */
#define CFG_FPINT_MASK	0x1c000000 	/* select fpa interrupt (0-5) */
#define CFG_FPINT_SHIFT	26
#define CFG_HALT	0x02000000 	/* halt until interrupt */
#define CFG_RF		0x01000000	/* reduce frequency */
#define CFG_AC		0x00800000	/* alt cache: 8kb+8kb */

/* extra CP0 registers */

#ifdef __ASSEMBLER__

#define C0_CONFIG	$3

$config		= 	$3

#else

#define C0_CONFIG	3

#endif /* __ASSEMBLER__ */

#endif /* _MIPS_R3081_H_ */
