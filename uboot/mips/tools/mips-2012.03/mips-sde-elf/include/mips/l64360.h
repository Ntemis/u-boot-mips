/*
 * Copyright (c) 1996-2003 MIPS Technologies, Inc.
 * Copyright (C) 2009 CodeSourcery LLC.
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
 * lsi/l64360.h: defines for LSI Logic L64360/ATMizer 
 */


#ifndef _MIPS_LR64360_H_
#define _MIPS_LR64360_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ATMizer based on LR333x0 */
#include "mips/lr33300.h"

/* redefine the kseg 0/1 testing functions: everything is kseg1 (uncached) */
#undef	IS_KVA
#undef	IS_KVA0
#undef	IS_KVA1
#undef	IS_KVA01
#undef	IS_KVA2
#undef	IS_UVA

#define	IS_KVA(v)	1
#define	IS_KVA0(v)	0
#define	IS_KVA1(v)	1
#define	IS_KVA01(v)	1
#define	IS_KVA2(v)	0
#define	IS_UVA(v)	0

/* special IRAM region */
#define IRAM_BASE	0x00000000	/* IRAM */
#define IRAM_SIZE	4096	
#define IS_IRAM(v)	((unsigned) (v) < IRAM_SIZE)

/* registers */
#define VCR_BASE    0xfff00000	/* VCR ram 				*/
#define M_CREDIT    0xfff04000	/* channel group credit register 	*/
#define M_CONFIG    0xfff04100	/* configuration register 		*/
#define M_STALL	    0xfff04200	/* stall register 			*/
#define M_PRPC      0xfff04300	/* peak rate pacing counter 		*/
#define M_RXBUFPTR  0xfff04400	/* current rx cell address 		*/
#define M_TXFIFO    0xfff04500	/* transmit address fifo 		*/
#define M_RXACK	    0xfff0460c	/* receive cell indicator 		*/
#define M_GPRR      0xfff04700	/* global pacing rate register 		*/
#define M_SCR	    0xfff04a00	/* system control register 		*/
#define M_AHI	    0xfff04b00	/* assert host interrupt 		*/
#define M_CRC32	    0xfff04c00	/* CRC32 partial result 		*/
#define M_ASUBR     0xfff04d00	/* address substitution register	*/
#define M_DMACR	    0x00400000	/* DMA control register 		*/

#ifndef __ASSEMBLER__
#define CREDIT		(*((volatile unsigned long *)M_CREDIT))
#define CONFIG		(*((volatile unsigned long *)M_CONFIG))
#define STALL		(*((volatile unsigned long *)M_STALL))
#define PRPC		(*((volatile unsigned long *)M_PRPC))
#define RXBUFPTR	(*((volatile unsigned long *)M_RXBUFPTR))
#define TXFIFO		(*((volatile unsigned long *)M_TXFIFO))
#define RXACK		(*((volatile unsigned long *)M_RXACK))
#define GPRR		(*((volatile unsigned long *)M_GPRR))
#define SCR		(*((volatile unsigned long *)M_SCR))
#define AHI		(*((volatile unsigned long *)M_AHI))
#define CRC32		(*((volatile unsigned long *)M_CRC32))
#define ASUBR		(*((volatile unsigned long *)M_ASUBR))
#define DMACR		(*((volatile unsigned long *)M_DMACR))

/* 
 * IRAM access functions
 */

/* Block copy */
void		iram_write (vaddr_t, unsigned int *, size_t);
void		iram_read (unsigned int *, vaddr_t, size_t);

/*
 * Special versions of mips_get/put which handle the on-chip IRAM.
 */
unsigned int	_iram_get (void *, size_t, int *);
int		_iram_put (void *, size_t, unsigned int);

#define mips_get_byte(addr, errp)	_iram_get (addr, 1, errp)
#define mips_get_half(addr, errp)	_iram_get (addr, 2, errp)
#define mips_get_word(addr, errp)	_iram_get (addr, 4, errp)
#define mips_get_dword(addr, errp)	_iram_get (addr, 8, errp)

#define mips_put_byte(addr, v)		_iram_put (addr, 1, v)
#define mips_put_half(addr, v)		_iram_put (addr, 2, v)
#define mips_put_word(addr, v)		_iram_put (addr, 4, v)
#define mips_put_dword(addr, v)		_iram_put (addr, 8, v)
#endif

/* PRPC */
#define PRPC_RRSHFT 2
#define PRPC_RRMASK (7<<2)
#define PRPC_I  (1<<6)

/* CGCR */
#define CGCR_BBMASK (7<<2)
#define CGCR_BBSHFT 2

/* M_SCR system control register */
#define SCR_TAFMASK 7		/* tx addr fifo */
#define SCR_TAFSHFT 0
#define SCR_AWD	    (1<<4)	/* automatic watch-dog time-out */
#define SCR_RWD	    (1<<5)	/* regular watch-dog time-out */
#define SCR_BOCMASK (3<<6)
#define SCR_BOCSHFT 6
#define SCR_CHMASK  (0x3f<<8)
#define SCR_CHSHFT  8
#define SCR_SAFE    (1<<14)
#define SCR_CRCERR  (1<<15)
#define SCR_BSSHFT  16
#define SCR_BSMASK  (7<<16)	/* buffer size */
#define SCR_BS4     (0<<16)
#define SCR_BS8     (1<<16)
#define SCR_BS16    (2<<16)
#define SCR_BS32   (3<<16)	/* rx buffer size 32 cells */
#define SCR_CBSMASK (3<<19)	/* cache block size */
#define SCR_CBS2    (0<<19)
#define SCR_CBS4    (1<<19)
#define SCR_HHMASK  (7<<21)
#define SCR_HHSHFT  21
#define SCR_HH0	    (1<<21)
#define SCR_HH1	    (1<<22)
#define SCR_HH2	    (1<<23)
#define SCR_BM	    (1<<24)
#define SCR_TI	    (1<<26)	/* tx init */
#define SCR_RI      (1<<27)	/* receive init */
#define SCR_TOMASK  (3<<28)	/* tx offset */
#define SCR_TOSHFT  28
#define SCR_ROMASK  (3<<30)	/* rx offset */
#define SCR_ROSHFT  30
#define SCR_TO52   (3<<28)	/* tx cell size 52 bytes */
#define SCR_RO52   (3<<30)	/* rx cell size 52 bytes */
#define SCR_TXHEC  (1<<21)	/* generate HEC on tx */
#define SCR_RXHEC  (1<<22)	/* expect HEC on receive */
#define SCR_CHKHEC (1<<23)	/* check HEC on receive */
#define SCR_RXINIT (1<<27)	/* enable receiver */


/* address modifiers when writing to M_TAF */
#define A_CRC10	    (1<<2)	/* generate CRC10 value 		p39 */

/* address modifiers when writing to M_DMA 			  p28 & p52 */
#define DMA_LOMASK  (3<<30)	/* local offset register (VCR) */
#define DMA_LOSHFT  30	
#define DMA_BCMASK  (0x3f<<24)	/* transfer length counter */
#define DMA_BCSHFT  24
#define DMA_RD	    (1<<14)	/* read (versus write) */
#define DMA_WR	    0		/* rite (default) */
#define DMA_G	    (1<<13)	/* ghost write */
#define DMA_BCSHFT  24
#define DMA_LAMASK  (0x3ff<<2)	/* local address counter (VCR) */
#define DMA_LASHFT  2

/* RT stuff								p28 */
#define RT_MARMASK  (0xff<<24)	/* memory address register */
#define RT_MARSHFT  24
#define RT_MACMASK  (0x3fffff<<2) /* memory address counter */
#define RT_MACSHFT  2
#define RT_MORMASK  (3<<0)	/* memory (byte) offset register */
#define RT_MORSHFT  0

/* SP_AD 								p45 */
#define SPAD_BEMASK (0xf<<28)	/* byte enables */
#define SPAD_AT	    (1<<26)	/* access type */
#define SPAD_BF     (1<<25)	/* block fetch */
#define SPAD_ATOM   (1<<24)	/* atomic */


#ifdef __cplusplus
}
#endif
#endif /* _MIPS_LR33300_H_ */
