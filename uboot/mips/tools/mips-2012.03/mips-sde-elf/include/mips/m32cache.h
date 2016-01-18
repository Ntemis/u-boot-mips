/*
 * Copyright (c) 2006-2007 MIPS Technologies, Inc.
 * Copyright (c) CodeSourcery, Inc.
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
 * m32cache.h: MIPS32 cache support functions for MIPS SDE
 */


/*	
 * Note:	 pessimistic hazard timings assumed.
 */

#if CACHE_IS_M32 

	.set	nomips16	
/* we must fix this so that this module can compile with "generic" flags */
#if __mips != 32 && __mips != 64 && !defined(CPU_IS_4K) && !defined(CPU_IS5K)
#error use -mips32 or -mips64 options with this file
#endif
	
#define _BOOTCODE
#include <mips/asm.h>
#include <mips/regdef.h>
#include <mips/m32c0.h>
#include <mips/prid.h>


/*
 * MIPS32 cache operations.
 *
 * The _flush and _clean functions are complex composites that do whatever
 * is necessary to flush/clean ALL caches, in the quickest possible way.
 * The other functions are targetted explicitly at a particular cache
 * I or D; it is up to the user to call the correct set of functions
 * for a given system.
 */

IMPORT(mips_icache_size,4)
IMPORT(mips_icache_linesize,4)
IMPORT(mips_icache_ways,4)
	
IMPORT(mips_dcache_size,4)
IMPORT(mips_dcache_linesize,4)
IMPORT(mips_dcache_ways,4)
	
IMPORT(mips_scache_size,4)
IMPORT(mips_scache_linesize,4)
IMPORT(mips_scache_ways,4)
	
/*
 * Macros to automate cache operations
 */

#define addr	t0
#define maxaddr	t1
#define mask	t2

#define cacheop(kva, n, linesize, op)	\
	.set	noreorder ;		\
	/* check for bad size */	\
 	blez	n,11f ;			\
	addu	maxaddr,kva,n ;		\
	/* align to line boundaries */	\
	subu	mask,linesize,1 ;	\
	not	mask ;			\
	and	addr,kva,mask ;		\
	addu	maxaddr,-1 ;		\
	and	maxaddr,mask ;		\
	/* the cacheop loop */		\
10: 	cache	op,0(addr) ;	 	\
	bne     addr,maxaddr,10b ;	\
	addu   	addr,linesize ;		\
11:	.set	reorder
		
/* virtual cache op: no limit on size of region */
#define vcacheop(kva, n, linesize, op)	\
	cacheop(kva, n, linesize, op)

/* indexed cache op: region limited to cache size */
#define icacheop(kva, n, linesize, size, op) \
	move	t3,n;			\
	bltu	n,size,12f ;		\
	move	t3,size ;		\
12:	cacheop(kva, t3, linesize, op)
	

#if defined(IN_PMON) || defined(_SDE_CACHE_EXTRA) || defined(ITROM)
/* caches are always sized first */
#define SIZE_CACHE(reg,which)		\
	lw	reg,which;		\
	blez	reg,9f;			\
	sync	
#else	
/* caches may not have been sized yet */	
#define SIZE_CACHE(reg,which)		\
	lw	reg,which;		\
	move	v1,ra;			\
	bgez	reg,9f;			\
	bal	m32_size_cache;		\
	lw	reg,which;		\
	move	ra,v1;			\
9:	blez	reg,9f;			\
	sync	
#endif

#ifndef _SDE_CACHE_EXTRA	

#define tmp		t0	
#define cfg		t1
#define icachesize	t2
#define ilinesize	t3
#define iways		ta0
#define dcachesize	ta1
#define dlinesize	ta2
#define dways		ta3
#define scachesize	t8	
#define slinesize	t9
#define sways		v0

#endif

#endif /* CACHE_IS_M32 */
