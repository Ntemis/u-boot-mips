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
 * r36100.h: IDT R36100 specific register structure definitions
 */


#ifndef _MIPS_R36100_H_
#define _MIPS_R36100_H_

/* generic R3000 definitions */
#include "mips/r3kc0.h"

#ifdef __cplusplus
extern "C" {
#endif

#define R36100_BASE		0xffffe000

#ifdef __ASSEMBLER__

/* offsets from base register */
#if #endian(little)
#define R36100W(x)		(x)
#define R36100H(x)		(x)
#define R36100B(x)		(x)
#endif
#if #endian(big)
#define R36100W(x)		(x)
#define R36100H(x)		((x)^2)
#define R36100B(x)		((x)^3)
#endif

#else /* !__ASSEMBLER__ */

/* offsets from base pointer, this construct allows optimisation */
#if #endian(little)
#define R36100W(x)		*(volatile unsigned long *)(_r36100p + (x))
#define R36100H(x)		*(volatile unsigned short *)(_r36100p + (x))
#define R36100B(x)		*(volatile unsigned char *)(_r36100p + (x))
#endif
#if #endian(big)
#define R36100W(x)		*(volatile unsigned long *)(_r36100p + (x))
#define R36100H(x)		*(volatile unsigned short *)(_r36100p + ((x)^2))
#define R36100B(x)		*(volatile unsigned char *)(_r36100p + ((x)^3))
#endif

#define p36100	char *const _r36100p = (char * const)R36100_BASE

#endif /* __ASSEMBLER__ */

/* DRAM Controller */
#define DramRefreshCountReg	R36100H(0x100)
#define DramRefreshCompReg	R36100H(0x104)
#define DramRasMuxSelReg1_0	R36100H(0x110)
#define DramRasMuxSelReg3_2	R36100H(0x114)
#define DramCasMuxSelReg1_0	R36100H(0x120)
#define DramCasMuxSelReg3_2	R36100H(0x124)

#define DramRefreshDisable	0xfc00
/* DramRasMuxSel */
#define   DramRas13_A26		0x2000
#define   DramRas13_A24		0x0000
#define   DramRas12_A23		0x1000
#define   DramRas12_A10		0x0000
#define   DramRas11_A22		0x0800
#define   DramRas11_A20		0x0000
#define   DramRas10_A19		0x0400
#define   DramRas10_A10		0x0000
#define   DramRas9_A18		0x0200
#define   DramRas9_A9		0x0000
#define   DramRas4_A25		0x0010
#define   DramRas4_A13		0x0000
#define   DramRas3_A22		0x0008
#define   DramRas3_A12		0x0000
#define   DramRas2_A21		0x0004
#define   DramRas2_A11		0x0000

/* DramCasMuxSelReg */
#define   DramCas13_A13		0x2000
#define   DramCas13_A1		0x0000
#define   DramCas12_A24		0x1000
#define   DramCas12_A12		0x0000
#define   DramCas11_A11		0x0800
#define   DramCas11_A1		0x0000
#define   DramCas10_A10		0x0400
#define   DramCas10_A1		0x0000
#define   DramCas9_A9		0x0200
#define   DramCas9_A0		0x0000
#define   DramCas2_A20		0x0004
#define   DramCas2_A2		0x0000

/* Common DRAM configurations */
#define	  DramRas16Mx64	(DramRas13_A26|DramRas12_A23| \
			 DramRas11_A22|DramRas10_A19| \
			 DramRas9_A18 |DramRas4_A25| \
			 DramRas3_A12 |DramRas2_A21)
#define	  DramCas16Mx64	(DramCas13_A13|DramCas12_A24| \
			 DramCas11_A11|DramCas10_A10| \
			 DramCas9_A9  |DramCas2_A20)

#define	  DramRas4Mx64	(	       DramRas12_A23| \
			 DramRas11_A22|DramRas10_A19| \
			 DramRas9_A18 |DramRas4_A13| \
			 DramRas3_A12 |DramRas2_A21)
#define	  DramCas4Mx64	(              DramCas12_A24| \
			 DramCas11_A11|DramCas10_A10| \
			 DramCas9_A9  |DramCas2_A20)

#define	  DramRas1Mx64	(DramRas11_A22|DramRas10_A19| \
			 DramRas9_A18 |DramRas4_A13| \
			 DramRas3_A12 |DramRas2_A21)
#define	  DramCas1Mx64	(DramCas11_A11|DramCas10_A10| \
			 DramCas9_A9  |DramCas2_A20)

#define	  DramRas256Kx64 (	       DramRas10_A19| \
			 DramRas9_A18 |DramRas4_A13| \
			 DramRas3_A12 |DramRas2_A11)
#define	  DramCas256Kx64 (             DramCas10_A10| \
			 DramCas9_A9  |DramCas2_A20)

#define	  DramRas16Mx32	(DramRas13_A24|DramRas12_A23| \
			 DramRas11_A20|DramRas10_A19| \
			 DramRas9_A18 |DramRas4_A25| \
			 DramRas3_A22 |DramRas2_A21)
#define	  DramCas16Mx32	(DramCas13_A13|DramCas12_A12| \
			 DramCas11_A11|DramCas10_A10| \
			 DramCas9_A9  |DramCas2_A2)

#define	  DramRas4Mx32	(	       DramRas12_A23| \
			 DramRas11_A20|DramRas10_A19| \
			 DramRas9_A18 |DramRas4_A13| \
			 DramRas3_A22 |DramRas2_A21)
#define	  DramCas4Mx32	(              DramCas12_A12| \
			 DramCas11_A11|DramCas10_A10| \
			 DramCas9_A9  |DramCas2_A2)

#define	  DramRas1Mx32	(DramRas11_A20|DramRas10_A19| \
			 DramRas9_A18 |DramRas4_A13| \
			 DramRas3_A12 |DramRas2_A21)
#define	  DramCas1Mx32	(DramCas11_A11|DramCas10_A10| \
			 DramCas9_A9  |DramCas2_A2)

#define	  DramRas256Kx32 (	       DramRas10_A19| \
			 DramRas9_A18 |DramRas4_A13| \
			 DramRas3_A12 |DramRas2_A11)
#define	  DramCas256Kx32 (             DramCas10_A10| \
			 DramCas9_A9  |DramCas2_A2)


#define DramMSBBaseAddrReg0	R36100H(0x180)
#define DramMSBBankMaskReg0	R36100H(0x184)
#define DramLSBControlReg0	R36100H(0x188)
#define DramMSBControlReg0	R36100H(0x18c)
#define DramMSBBaseAddrReg1	R36100H(0x190)
#define DramMSBBankMaskReg1	R36100H(0x194)
#define DramLSBControlReg1	R36100H(0x198)
#define DramMSBControlReg1	R36100H(0x19c)
#define DramMSBBaseAddrReg2	R36100H(0x1a0)
#define DramMSBBankMaskReg2	R36100H(0x1a4)
#define DramLSBControlReg2	R36100H(0x1a8)
#define DramMSBControlReg2	R36100H(0x1ac)
#define DramMSBBaseAddrReg3	R36100H(0x1b0)
#define DramMSBBankMaskReg3	R36100H(0x1b4)
#define DramLSBControlReg3	R36100H(0x1b8)
#define DramMSBControlReg3	R36100H(0x1bc)

/* DramLSBControlReg */
#define DramLSBControlMask16Mx64	0xf000
#define DramLSBControlMask16Mx32	0xc000
#define DramLSBControlMask16Mx16	0xe000
#define DramLSBControlMask4Mx64		0xf000
#define DramLSBControlMask4Mx32		0xe000
#define DramLSBControlMask4Mx16		0xfc00
#define DramLSBControlMask1Mx64		0xf000
#define DramLSBControlMask1Mx32		0xf000
#define DramLSBControlMask1Mx16		0xf800
#define DramLSBControlMask256Kx64	0xf800
#define DramLSBControlMask256Kx32	0xf800
#define DramLSBControlMask256Kx16	0xfc00
#define DramLSBControlMaskSmallest	0xfc00

#define DramLSBControlTypeFCT260	0x0040
#define DramLSBControlTypeFCT245	0x0020
#define DramLSBControlTypeFCT543	0x0000

#define DramLSBControlPort64		0x0018
#define DramLSBControlPort32		0x0000
#define DramLSBControlPort16		0x0010

#define DramLSBControlPageAfterBurstRd	0x0004
#define DramLSBControlPageAfterSingleRd	0x0002
#define DramLSBControlPageAfterWrite	0x0001

#define   DramMSBControlRASP3		0x8000
#define   DramMSBControlRASP2		0x4000
#define   DramMSBControlRASP1		0x0000

#define   DramMSBControlRASAddrHold1_5	0x2000
#define   DramMSBControlRASAddrHold0_5	0x0000

#define   DramMSBControlRASAddrSetup1_5	0x1000
#define   DramMSBControlRASAddrSetup0_5	0x0000

#define   DramMSBControlCASWidth2_5	0x0800
#define   DramMSBControlCASWidth1_5	0x0400

#define   DramMSBControlRdBTA3		0x0300
#define   DramMSBControlRdBTA2		0x0200
#define   DramMSBControlRdBTA1		0x0100
#define   DramMSBControlRdBTA0		0x0000

#define   DramMSBControlWrBTA1		0x0040
#define   DramMSBControlWrBTA0		0x0040

#define	  DramMSBControlBrstAckLast	0x001f
#define	  DramMSBControlBrstAckShift	0

/* Memory/IO Controller */
#define MemLSBBaseAddrReg0	R36100H(0x200)
#define MemMSBBaseAddrReg0	R36100H(0x204)
#define MemLSBBankMask0		R36100H(0x208)
#define MemMSBBankMask0		R36100H(0x20c)
#define MemControlReg0		R36100H(0x210)
#define MemLSBWaitStateReg0	R36100H(0x214)
#define MemMSBWaitStateReg0	R36100H(0x218)
#define MemLSBBaseAddrReg1	R36100H(0x220)
#define MemMSBBaseAddrReg1	R36100H(0x224)
#define MemLSBBankMask1		R36100H(0x228)
#define MemMSBBankMask1		R36100H(0x22c)
#define MemControlReg1		R36100H(0x230)
#define MemLSBWaitStateReg1	R36100H(0x234)
#define MemMSBWaitStateReg1	R36100H(0x238)
#define MemLSBBaseAddrReg2	R36100H(0x240)
#define MemMSBBaseAddrReg2	R36100H(0x244)
#define MemLSBBankMask2		R36100H(0x248)
#define MemMSBBankMask2		R36100H(0x24c)
#define MemControlReg2		R36100H(0x250)
#define MemLSBWaitStateReg2	R36100H(0x254)
#define MemMSBWaitStateReg2	R36100H(0x258)
#define MemLSBBaseAddrReg3	R36100H(0x260)
#define MemMSBBaseAddrReg3	R36100H(0x264)
#define MemLSBBankMask3		R36100H(0x268)
#define MemMSBBankMask3		R36100H(0x26c)
#define MemControlReg3		R36100H(0x270)
#define MemLSBWaitStateReg3	R36100H(0x274)
#define MemMSBWaitStateReg3	R36100H(0x278)
#define MemLSBBaseAddrReg4	R36100H(0x280)
#define MemMSBBaseAddrReg4	R36100H(0x284)
#define MemLSBBankMask4		R36100H(0x288)
#define MemMSBBankMask4		R36100H(0x28c)
#define MemControlReg4		R36100H(0x290)
#define MemLSBWaitStateReg4	R36100H(0x294)
#define MemMSBWaitStateReg4	R36100H(0x298)
#define MemLSBBaseAddrReg5	R36100H(0x2a0)
#define MemMSBBaseAddrReg5	R36100H(0x2a4)
#define MemLSBBankMask5		R36100H(0x2a8)
#define MemMSBBankMask5		R36100H(0x2ac)
#define MemControlReg5		R36100H(0x2b0)
#define MemLSBWaitStateReg5	R36100H(0x2b4)
#define MemMSBWaitStateReg5	R36100H(0x2b8)
#define MemLSBBaseAddrReg6	R36100H(0x2c0)
#define MemMSBBaseAddrReg6	R36100H(0x2c4)
#define MemLSBBankMask6		R36100H(0x2c8)
#define MemMSBBankMask6		R36100H(0x2cc)
#define MemControlReg6		R36100H(0x2d0)
#define MemLSBWaitStateReg6	R36100H(0x2d4)
#define MemMSBWaitStateReg6	R36100H(0x2d8)
#define MemLSBBaseAddrReg7	R36100H(0x2e0)
#define MemMSBBaseAddrReg7	R36100H(0x2e4)
#define MemLSBBankMask7		R36100H(0x2e8)
#define MemMSBBankMask7		R36100H(0x2ec)
#define MemControlReg7		R36100H(0x2f0)
#define MemLSBWaitStateReg7	R36100H(0x2f4)
#define MemMSBWaitStateReg7	R36100H(0x2f8)

/* MemControlReg:Type */
#define   MemControlPCMCIAMem	0x0b00
#define   MemControlPCMCIAIO	0x0a00
#define   MemControlMotorola	0x0900
#define   MemControlIntel	0x0800
#define   MemControlFCT260	0x0200
#define   MemControlFCT245	0x0100
#define   MemControlFCT543	0x0000
/* MemControl:Size */
#define   MemControl64		0x00c0
#define   MemControl16		0x0080
#define   MemControl8		0x0040
#define   MemControl32		0x0000

/* MemLSBWait */
#define   MemLSBWaitRdStart2DatumShift	12
#define   MemLSBWaitWrStart2DatumShift	8
#define   MemLSBWaitRdDatum2DatumShift	4
#define   MemLSBWaitWrDatum2DatumShift	0

/* MemMSBWait */
#define   MemMSBWaitStartRepeat		0x4000
#define	  MemMSBWaitStart2BurstAckShift	8
#define   MemMSBWaitBen			0x0040
#define   MemMSBWaitBTAShift		0

#define DmaLSBSourceAddrReg0	R36100H(0x300)
#define DmaMSBSourceAddrReg0	R36100H(0x304)
#define DmaLSBTargetAddrReg0	R36100H(0x308)
#define DmaMSBTargetAddrReg0	R36100H(0x30c)
#define DmaLSBCountReg0		R36100H(0x310)
#define DmaMSBCountReg0		R36100H(0x314)
#define DmaLSBControlReg0	R36100H(0x318)
#define DmaMSBControlReg0	R36100H(0x31c)
#define DmaLSBSourceAddrReg1	R36100H(0x320)
#define DmaMSBSourceAddrReg1	R36100H(0x324)
#define DmaLSBTargetAddrReg1	R36100H(0x328)
#define DmaMSBTargetAddrReg1	R36100H(0x32c)
#define DmaLSBCountReg1		R36100H(0x330)
#define DmaMSBCountReg1		R36100H(0x334)
#define DmaLSBControlReg1	R36100H(0x338)
#define DmaMSBControlReg1	R36100H(0x33c)
#define DmaLSBSourceAddrReg2	R36100H(0x340)
#define DmaMSBSourceAddrReg2	R36100H(0x344)
#define DmaLSBTargetAddrReg2	R36100H(0x348)
#define DmaMSBTargetAddrReg2	R36100H(0x34c)
#define DmaLSBCountReg2		R36100H(0x350)
#define DmaMSBCountReg2		R36100H(0x354)
#define DmaLSBControlReg2	R36100H(0x358)
#define DmaMSBControlReg2	R36100H(0x35c)
#define DmaLSBSourceAddrReg3	R36100H(0x360)
#define DmaMSBSourceAddrReg3	R36100H(0x364)
#define DmaLSBTargetAddrReg3	R36100H(0x368)
#define DmaMSBTargetAddrReg3	R36100H(0x36c)
#define DmaLSBCountReg3		R36100H(0x370)
#define DmaMSBCountReg3		R36100H(0x374)
#define DmaLSBControlReg3	R36100H(0x378)
#define DmaMSBControlReg3	R36100H(0x37c)
#define DmaLSBSourceAddrRegA	R36100H(0x380)
#define DmaMSBSourceAddrRegA	R36100H(0x384)
#define DmaLSBTargetAddrRegA	R36100H(0x388)
#define DmaMSBTargetAddrRegA	R36100H(0x38c)
#define DmaLSBCountRegA		R36100H(0x390)
#define DmaMSBCountRegA		R36100H(0x394)
#define DmaLSBControlRegA	R36100H(0x398)
#define DmaMSBControlRegA	R36100H(0x39c)
#define DmaLSBSourceAddrRegB	R36100H(0x3a0)
#define DmaMSBSourceAddrRegB	R36100H(0x3a4)
#define DmaLSBTargetAddrRegB	R36100H(0x3a8)
#define DmaMSBTargetAddrRegB	R36100H(0x3ac)
#define DmaLSBCountRegB		R36100H(0x3b0)
#define DmaMSBCountRegB		R36100H(0x3b4)
#define DmaLSBControlRegB	R36100H(0x3b8)
#define DmaMSBControlRegB	R36100H(0x3bc)
#define DmaLSBSourceAddrRegC	R36100H(0x3c0)
#define DmaMSBSourceAddrRegC	R36100H(0x3c4)
#define DmaLSBTargetAddrRegC	R36100H(0x3c8)
#define DmaMSBTargetAddrRegC	R36100H(0x3cc)
#define DmaLSBCountRegC		R36100H(0x3d0)
#define DmaMSBCountRegC		R36100H(0x3d4)
#define DmaLSBControlRegC	R36100H(0x3d8)
#define DmaMSBControlRegC	R36100H(0x3dc)
#define DmaLSBSourceAddrRegD	R36100H(0x3e0)
#define DmaMSBSourceAddrRegD	R36100H(0x3e4)
#define DmaLSBTargetAddrRegD	R36100H(0x3e8)
#define DmaMSBTargetAddrRegD	R36100H(0x3ec)
#define DmaLSBCountRegD		R36100H(0x3f0)
#define DmaMSBCountRegD		R36100H(0x3f4)
#define DmaLSBControlRegD	R36100H(0x3f8)
#define DmaMSBControlRegD	R36100H(0x3fc)

#define ExtDMAControlReg0	R36100H(0x400)
#define ExtDMAControlReg1	R36100H(0x410)

#define   ExtDmaControlStopChan		0x8000
#define   ExtDmaControlReqHigh		0x4000
#define   ExtDmaControlGntHigh		0x2000
#define   ExtDmaControlSampleLate	0x0800

#define DebugTraceControlReg	R36100H(0x500)
#define DebugDebugControlReg	R36100H(0x504)
#define DebugLSBTraceAddrReg0	R36100H(0x510)
#define DebugMSBTraceAddrReg0	R36100H(0x514)
#define DebugLSBTraceAddrReg1	R36100H(0x520)
#define DebugMSBTraceAddrReg1	R36100H(0x524)

#define SerialCommand1		R36100B(0x800)
#define SerialData1		R36100B(0x804)
#define SerialCommand0		R36100B(0x808)
#define SerialData0		R36100B(0x80c)
#define SerialReset		R36100W(0x810)

#define TimerPrescalerCountReg	R36100H(0x900)
#define TimerPWMCountReg	R36100H(0x904)
#define TimerCountReg0		R36100H(0x910)
#define TimerCompareReg0	R36100H(0x914)
#define TimerPWMReg0		R36100H(0x918)
#define TimerControlReg0	R36100H(0x91c)
#define TimerCountReg1		R36100H(0x920)
#define TimerCompareReg1	R36100H(0x924)
#define TimerControlReg1	R36100H(0x92c)
#define TimerCountReg2		R36100H(0x930)
#define TimerCompareReg2	R36100H(0x934)
#define TimerControlReg2	R36100H(0x93c)

#define   TimerControlLock	0x8000
#define   TimerControlLockCC	0x4000
#define   TimerControlAck	0x2000
#define   TimerControlTC	0x1000
#define   TimerControlGate	0x0800
#define   TimerControlBTO	0x0400
#define   TimerControlTimerDis	0x0200
#define	  TimerControlPsel32768	0x000f
#define	  TimerControlPsel16384	0x000e
#define	  TimerControlPsel8192	0x000d
#define	  TimerControlPsel4096	0x000c
#define	  TimerControlPsel2048	0x000b
#define	  TimerControlPsel1024	0x000a
#define	  TimerControlPsel512	0x0009
#define	  TimerControlPsel256	0x0008
#define	  TimerControlPsel128	0x0007
#define	  TimerControlPsel64	0x0006
#define	  TimerControlPsel32	0x0005
#define	  TimerControlPsel16	0x0004
#define	  TimerControlPsel8	0x0003
#define	  TimerControlPsel4	0x0002
#define	  TimerControlPsel2	0x0001
#define	  TimerControlPsel1	0x0000

#define PioDataReg0		R36100H(0xa00)
#define PioDirReg0		R36100H(0xa04)
#define PioEffectSelReg0	R36100H(0xa08)
#define PioDataReg1		R36100H(0xa10)
#define PioDirReg1		R36100H(0xa14)
#define PioEffectSelReg1	R36100H(0xa18)
#define PioDataReg2		R36100H(0xa20)
#define PioDirReg2		R36100H(0xa24)
#define PioEffectSelReg2	R36100H(0xa28)

#define   PioLock		0x8000
#define   PioMask		0x7fff

#define   Pio0Pin14		0x4000
#define   Pio0Pin13		0x2000
#define   Pio0Pin12		0x1000
#define   Pio0Pin11		0x0800
#define   Pio0Pin10		0x0400
#define   Pio0Pin9		0x0200
#define   Pio0Pin8		0x0100
#define   Pio0Pin7		0x0080
#define   Pio0Pin6		0x0040
#define   Pio0Pin5		0x0020
#define   Pio0Pin4		0x0010
#define   Pio0Pin3		0x0008
#define   Pio0Pin2		0x0004
#define   Pio0Pin1		0x0002
#define   Pio0Pin0		0x0001
#define   Pio1Pin32		0x4000
#define   Pio1Pin31		0x2000
#define   Pio1Pin30		0x1000
#define   Pio1Pin29		0x0800
#define   Pio1Pin28		0x0400
#define   Pio1Pin27		0x0200
#define   Pio1Pin26		0x0100
#define   Pio1Pin25		0x0080
#define   Pio1Pin24		0x0040
#define   Pio1Pin23		0x0020
#define   Pio1Pin22		0x0010
#define   Pio1Pin21		0x0008
#define   Pio1Pin20		0x0004
#define   Pio1Pin19		0x0002
#define   Pio1Pin18		0x0001
#define   Pio2Pin17		0x4000
#define   Pio2Pin16		0x2000
#define   Pio2Pin15		0x1000
#define   Pio2Pin41		0x0800
#define   Pio2Pin40		0x0400
#define   Pio2Pin39		0x0200
#define   Pio2Pin38		0x0100
#define   Pio2Pin37		0x0080
#define   Pio2Pin36		0x0040
#define   Pio2Pin35		0x0020
#define   Pio2Pin34		0x0010
#define   Pio2Pin33		0x0008

#define   Pio0SerialTxData0	Pio0Pin14
#define   Pio0SerialRTS0	Pio0Pin13
#define   Pio0SerialDTR0	Pio0Pin12
#define   Pio0SerialTxData1	Pio0Pin11
#define   Pio0SerialRTS1	Pio0Pin10
#define   Pio0SerialDTR1	Pio0Pin9
#define   Pio0LaserVideoData	Pio0Pin8
#define   Pio0CentAck		Pio0Pin7
#define   Pio0CentBusy		Pio0Pin6
#define   Pio0CentPerror	Pio0Pin5
#define   Pio0CenSelect		Pio0Pin4
#define   Pio0CentFault		Pio0Pin3
#define   Pio0CentHostOEn	Pio0Pin2
#define   Pio0CentHostStrobe	Pio0Pin1
#define   Pio0DMABusGnt1	Pio0Pin0

#define   Pio1SerialCTS0	Pio1Pin32
#define   Pio1SerialDCD0	Pio1Pin31
#define   Pio1SerialRxData1	Pio1Pin30
#define   Pio1SerialPClkIn	Pio1Pin29
#define   Pio1SerialCTS1	Pio1Pin28
#define   Pio1SerialDCD1	Pio1Pin27
#define   Pio1LaserVideoClkIn	Pio1Pin26
#define   Pio1LaserLineSync	Pio1Pin25
#define   Pio1LaserPageSync	Pio1Pin24
#define   Pio1CentStrobe	Pio1Pin23
#define   Pio1CentAutoFeed	Pio1Pin22
#define   Pio1CentInit		Pio1Pin21
#define   Pio1CentSelect	Pio1Pin20
#define   Pio1DMABUSReq1	Pio1Pin19
#define   Pio1ExcInt4		Pio1Pin18

#define   Pio2ExcInt3		Pio2Pin17
#define   Pio2BrCond3		Pio2Pin16
#define   Pio2BrCond2		Pio2Pin15
#define   Pio2SerialRxData0	Pio2Pin41
#define   Pio2SerialPclkIn0	Pio2Pin40
#define   Pio2SerialSClk0	Pio2Pin39
#define   Pio2SerialSync0	Pio2Pin38
#define   Pio2SerialSClk1	Pio2Pin37
#define   Pio2SerialSync1	Pio2Pin36
#define   Pio2TimerTcGate2	Pio2Pin35
#define   Pio2TimerTcGate1	Pio2Pin34
#define   Pio2TimerTcGate0	Pio2Pin33

#define ExpIntPendReg0		R36100H(0xb00)
#define ExpIntMaskReg0		R36100H(0xb04)
#define ExpIntPendReg1		R36100H(0xb10)
#define ExpIntMaskReg1		R36100H(0xb14)
#define ExpIntDMASelReg		R36100H(0xb84)

#define   ExpInt1Serial		0x0010
#define   ExpInt1SerialRx1	0x0008
#define   ExpInt1SerialRx0	0x0004
#define   ExpInt1SerialTx1	0x0002
#define   ExpInt1SerialTx0	0x0001

#define   ExpInt0CentRead	0x4000
#define   ExpInt0CentWrite	0x2000
#define   ExpInt0CentReset	0x1000
#define   ExpInt0LaserVideoBand	0x0800
#define   ExpInt0LaserFIFONotFull 0x0400
#define   ExpInt0VideoPage	0x0200
#define   ExpInt0VideoLine	0x0100
#define   ExpInt0TimerTC2	0x0080
#define   ExpInt0TimerTC1	0x0040
#define   ExpInt0TimerTC0	0x0020
#define   ExpInt0DMADone3	0x0008
#define   ExpInt0DMADone2	0x0004
#define   ExpInt0DMADone1	0x0002
#define   ExpInt0DMADone0	0x0001

#define CentSubModeReg		R36100H(0xc00)
#define CentStatusReg		R36100H(0xc04)
#define CentControlReg		R36100H(0xc08)
#define CentNibbleDataReg	R36100H(0xc0c)
#define CentHostStatusReg	R36100H(0xc10)
#define CentDelayReg		R36100H(0xc14)

#define LaserControlReg		R36100H(0xd00)
#define LaserVertSkipReg	R36100H(0xd04)
#define LaserHorSkipReg		R36100H(0xd08)
#define LaserBandLineCountReg	R36100H(0xd0c)
#define LaserPixelWordCountReg	R36100H(0xd10)
#define LaserDataReg		R36100W(0xd20)


/* extra CP0 registers */

#ifdef __ASSEMBLER__

#define C0_CONFIG	$3

$config		= 	$3

#else

#define C0_CONFIG	3

#endif /* __ASSEMBLER__ */

#define CFG_LOCK	0x80000000	/* lock register */
#define CFG_RSVD	0x40000000	/* reserved: write as 1 */
#define CFG_DBREFILL	0x20000000	/* data bus refill: 1/4 words */
#define CFG_DCI9_8	0x00000000	/* DCache Index PhyAddr 9 & 8 */
#define CFG_DCI28_8	0x10000000	/* DCache Index PhyAddr 28 & 8 */
#define CFG_DCI28_27	0x18000000	/* DCache Index PhyAddr 28 & 27 */
#define CFG_HALT	0x02000000 	/* halt until interrupt */
#define CFG_ICI11_10	0x00000000	/* ICache Index PhyAddr 11 & 10 */
#define CFG_ICI28_10	0x01000000	/* ICache Index PhyAddr 28 & 10 */
#define CFG_ICI28_27	0x01800000	/* ICache Index PhyAddr 28 & 27 */
#define CFG_RFMASK	0x00700000	/* reduce frequency mask*/
#define CFG_RFSHIFT	20		/* reduce frequency shift */
#define CFG_FDCM	0x00080000	/* force Dcache miss */
#define CFG_FICM	0x00040000	/* force Icache miss */
#define CFG_DWRD	0x00020000	/* Dcache write disable */
#define CFG_IWRD	0x00010000	/* Icache write disable */

#ifdef __cplusplus
}
#endif

#endif /* _MIPS_R36100_H_ */
