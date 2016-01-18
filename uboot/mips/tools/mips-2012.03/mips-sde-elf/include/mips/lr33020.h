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
 * lsi/lr33000.h: defines for LSI Logic LR33020
 */


#ifndef _MIPS_LR33020_H_
#define _MIPS_LR33020_H_

#include "mips/lr33000.h"

#ifndef __ASSEMBLER__
#define C2_SRCSKEW	0	/* graphics source skew */
#define C2_SRCSHIFT	1	/* graphics source shift */
#define C2_COLOR0	2	/* COLOR0 data */
#define C2_COLOR1	3	/* COLOR1 data */
#define C2_GCPCNTRL	4	/* graphics control */
#define C2_RASTEROP	5	/* RasterOp logical operation */
#define C2_PLANEMASK	6	/* Plane mask */
#define C2_CONFIG	9	/* video control */
#define C2_PSSTAT	24	/* I/O port status */
#define C2_PSCOMM	25	/* I/O port command */
#define C2_PSCOMMWE	27	/* I/O port write enable */

/* cp2 data registers */
#define C2_SCRSTART	0	/* Screen start address */
#define C2_SCRPITCH	1	/* Screen pitch */
#define C2_HWCRSRSTART	2	/* Hardware cursor start addr */
#define C2_HWCRSRCURR	3	/* Current hardware cursor addr */
#define C2_SAMEXTENT	4	/* VRAM serial-access-mode extent */
#define C2_NXTDISP	5	/* Next display addr */
#define C2_CURDISP	6	/* Current display address */
#define C2_LINECOUNT	7	/* Video line count */
#define C2_VBLKSIZE	8	/* Video block size */
#define C2_SRCLINE	9	/* Src start of next line addr */
#define C2_SRCCURR	10	/* Source current addr */
#define C2_SRCPITCH	11	/* Source pitch */
#define C2_DESTLINE	12	/* Dest start of next line addr */
#define C2_DESTCURR	13	/* Destination current addr */
#define C2_DESTPITCH	14	/* Destination pitch */
#define C2_GBLKSIZE	15	/* Graphics src read block size */
#define C2_SERPULS	16	/* Comp sync serration pulse width */
#define C2_HLINTR	17	/* Horizontal interrupt line */
#define C2_BLANKS	18	/* Blank start */
#define C2_SYNCS	19	/* SYNC start */
#define C2_SYNCRESET	20	/* SYNC reset */
#define C2_BLANKE	21	/* Blank end */
#define C2_HWCRSR	22	/* Hardware cursor location */
#define C2_VHWCONFIG	23	/* Video hardware config bits */
#define C2_PSTXB	24	/* PS/2 serial port Tx buffer */
#define C2_PSRCVB	25	/* PS/2 serial port Rx buffer */
#define C2_PSTXBWE	27	/* PS/2 serial port Tx buffer write enable */
#define C2_SRCDATA	28	/* Source data */
#define C2_DESTDATA	29	/* Destination data */
#define C2_LEFTMASK	30	/* Left edge mask */
#define C2_RIGHTMASK	31	/* Right edge mask */

#else

/* cp2 control registers */
#define C2_SRCSKEW	$0	/* graphics source skew */
#define C2_SRCSHIFT	$1	/* graphics source shift */
#define C2_COLOR0	$2	/* COLOR0 data */
#define C2_COLOR1	$3	/* COLOR1 data */
#define C2_GCPCNTRL	$4	/* graphics control */
#define C2_RASTEROP	$5	/* RasterOp logical operation */
#define C2_PLANEMASK	$6	/* Plane mask */
#define C2_CONFIG	$9	/* video control */
#define C2_PSSTAT	$24	/* I/O port status */
#define C2_PSCOMM	$25	/* I/O port command */
#define C2_PSCOMMWE	$27	/* I/O port write enable */

/* cp2 data registers */
#define C2_SCRSTART	$0	/* Screen start address */
#define C2_SCRPITCH	$1	/* Screen pitch */
#define C2_HWCRSRSTART	$2	/* Hardware cursor start addr */
#define C2_HWCRSRCURR	$3	/* Current hardware cursor addr */
#define C2_SAMEXTENT	$4	/* VRAM serial-access-mode extent */
#define C2_NXTDISP	$5	/* Next display addr */
#define C2_CURDISP	$6	/* Current display address */
#define C2_LINECOUNT	$7	/* Video line count */
#define C2_VBLKSIZE	$8	/* Video block size */
#define C2_SRCLINE	$9	/* Src start of next line addr */
#define C2_SRCCURR	$10	/* Source current addr */
#define C2_SRCPITCH	$11	/* Source pitch */
#define C2_DESTLINE	$12	/* Dest start of next line addr */
#define C2_DESTCURR	$13	/* Destination current addr */
#define C2_DESTPITCH	$14	/* Destination pitch */
#define C2_GBLKSIZE	$15	/* Graphics src read block size */
#define C2_SERPULS	$16	/* Comp sync serration pulse width */
#define C2_HLINTR	$17	/* Horizontal interrupt line */
#define C2_BLANKS	$18	/* Blank start */
#define C2_SYNCS	$19	/* SYNC start */
#define C2_SYNCRESET	$20	/* SYNC reset */
#define C2_BLANKE	$21	/* Blank end */
#define C2_HWCRSR	$22	/* Hardware cursor location */
#define C2_VHWCONFIG	$23	/* Video hardware config bits */
#define C2_PSTXB	$24	/* PS/2 serial port Tx buffer */
#define C2_PSRCVB	$25	/* PS/2 serial port Rx buffer */
#define C2_PSTXBWE	$27	/* PS/2 serial port Tx buffer write enable */
#define C2_SRCDATA	$28	/* Source data */
#define C2_DESTDATA	$29	/* Destination data */
#define C2_LEFTMASK	$30	/* Left edge mask */
#define C2_RIGHTMASK	$31	/* Right edge mask */

#define sstep		c2	0x00ffff
#define sbstep		c2	0x40ffff
#define wstep		c2	0x80ffff
#define wstep_l		c2	0x88ffff
#define wstep_r		c2	0x84ffff
#define wstep_l_r	c2	0x8cffff
#define wstep_s		c2	0xa0ffff
#define wstep_s_l	c2	0xa8ffff
#define wstep_s_r	c2	0xa4ffff
#define wstep_s_l_r	c2	0xacffff
#define wstep_sb	c2	0xb0ffff
#define wstep_sb_l	c2	0xb8ffff
#define wstep_sb_r	c2	0xb4ffff
#define wstep_sb_l_r	c2	0xbcffff
#define wstep_four	c2	0x82ffff
#define wstep_bfour	c2	0x81ffff
#define bstep_bfour	c2	0xc1ffff
#define bstep		c2	0xc0ffff
#define bstep_l		c2	0xc8ffff
#define bstep_r		c2	0xc4ffff
#define bstep_l_r	c2	0xccffff
#define bstep_s		c2	0xe0ffff
#define bstep_s_l	c2	0xe8ffff
#define bstep_s_r	c2	0xe4ffff
#define bstep_s_l_r	c2	0xecffff
#define bstep_sb	c2	0xf0ffff
#define bstep_sb_l	c2	0xf8ffff
#define bstep_sb_r	c2	0xf4ffff
#define bstep_sb_l_r	c2	0xfcffff

#endif /* __ASSEMBLER__ */

/* register bit assignments */
/* M_CFGREG */
#define CR_BANKMASK	(7<<5)
#define CR_BANKSHFT	5

/* C2_GCPCNTRL creg4 */
#define GCPC_SPCLWEMASK	0x00006000
#define GCPC_YDIR	(1<<12)
#define GCPC_XDIR	(1<<11)
#define GCPC_WO		(1<<9)
#define GCPC_MW		(1<<8)
#define GCPC_MASK	(1<<6)
#define GCPC_EXPND	(1<<4)
#define GCPC_TRAN	(1<<3)
#define GCPC_PIXSIZMASK	0x00000007

/* C2_VHWCNTRL creg9 */
#define VHWCNTRL_HCUR		(1<<19)
#define VHWCNTRL_DRAM		(1<<18)
#define VHWCNTRL_SAM		(1<<17)
#define VHWCNTRL_VRAM		(1<<16)
#define VHWCNTRL_D3		(1<<15)
#define VHWCNTRL_IORV3MASK 	(7<<12)
#define VHWCNTRL_IOWAIT3MASK 	(0xf<<8)
#define VHWCNTRL_D2		(1<<7)
#define VHWCNTRL_IORV2MASK 	(7<<4)
#define VHWCNTRL_IOWAIT2MASK 	(0xf<<0)

/* C2_PSSTAT creg24 */
#define PSSTAT_FERR	(1<<7)
#define PSSTAT_PAR	(1<<6)
#define PSSTAT_RXIN	(1<<5)
#define PSSTAT_RXBF	(1<<4)
#define PSSTAT_TXBE	(1<<3)
#define PSSTAT_TXIN	(1<<2)
#define PSSTAT_CLKX	(1<<1)
#define PSSTAT_SI1	(1<<1)
#define PSSTAT_CLK	(1<<0)
#define PSSTAT_SI0	(1<<0)

/* C2_PSCOMM creg25 */
#define PSCOMM_IO	(1<<7)
#define PSCOMM_CLKINH	(1<<4)
#define PSCOMM_RCVINT	(1<<3)
#define PSCOMM_TXINT	(1<<2)
#define PSCOMM_TXEN	(1<<1)
#define PSCOMM_SO1	(1<<1)
#define PSCOMM_INTHTX	(1<<0)
#define PSCOMM_SO0	(1<<0)

/* C2_VHWCONFIG dreg23 */
#define VHWCONFIG_EN		(1<<31)
#define VHWCONFIG_CROSSINV	(1<<18)
#define VHWCONFIG_CROSSDAT	(1<<17)
#define VHWCONFIG_CROSSEN	(1<<16)
#define VHWCONFIG_CSYNCEN	(1<<15)
#define VHWCONFIG_OVRSCN	(1<<14)
#define VHWCONFIG_VEND		(1<<13)
#define VHWCONFIG_VSYNCOUTEN	(1<<12)
#define VHWCONFIG_VSYNCINEN	(1<<11)
#define VHWCONFIG_HWCRSR	(1<<10)
#define VHWCONFIG_SHFTMASK	(3<<8)
#define VHWCONFIG_VSPOS		(1<<7)
#define VHWCONFIG_HSPOS		(1<<6)
#define VHWCONFIG_VSINT		(1<<5)
#define VHWCONFIG_HLINT		(1<<4)
#define VHWCONFIG_VLINTEN	(1<<1)
#define VHWCONFIG_HLINTEN	(1<<0)

#endif /* _MIPS_LR33020_H_ */
