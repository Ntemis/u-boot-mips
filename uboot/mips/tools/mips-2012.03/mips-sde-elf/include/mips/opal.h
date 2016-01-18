/*
 * Copyright (c) 2001-2003 MIPS Technologies, Inc.
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
 * mips/opal.h : MIPS "Opal" 5K family coprocessor 0 definitions
 */


#ifndef _MIPS_OPAL_H_
#define _MIPS_OPAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* MIPS64 compliant */
#include "mips/m64c0.h"

/*
 * Processor-specific fields in Status Register  (CP0 Register 12, Select 0)
 * (Pro cores only)
 */
#define SR_CEE		0x00020000 	/* CorExtend Enable */

/*
 * Processor-specific exceptions in Cause Register (CP0 Register 13, Select 0)
 * (Pro cores only)
 */
#define EXC_CEU		17		/* CorExtend Unusable */

/*
 * Processor-specific fields in Config0 Register  (CP0 Register 16, Select 0)
 */
#define CFG0_K23MASK	0x70000000	/* KSEG2/3 cacheability */
#define CFG0_K23SHIFT	28
#define CFG0_KUMASK	0x0e000000	/* KUSEG cacheability */
#define CFG0_KUSHIFT	25
#define CFG0_UDI	0x00400000	/* UDI present */
#define CFG0_SB		0x00200000	/* SimpleBE bus mode */
#define CFG0_ISD	0x00100000	/* instruction scheduling disable */
#define CFG0_WC		0x00080000	/* config write enable */
#define CFG0_DID	0x00020000	/* dual issue disable */
#define CFG0_BM		0x00010000	/* burst order (0 = incremental) */

/*
 * Processor-specific fields in Debug Register  (CP0 Register 23, Select 0)
 */
#define DBG_DBD		0x80000000	/* branch delay slot */
#define DBG_DM		0x40000000	/* in debug mode */
#define DBG_NoDCR	0x20000000	/* dseg is not present */
#define DBG_LSNM	0x10000000	/* load/store dseg/remain */
#define DBG_DOZE	0x08000000	/* was in low power mode */
#define DBG_HALT	0x04000000	/* system bus clock was running */
#define DBG_COUNTDM	0x02000000	/* count reg counts in debug mode */
#define DBG_IBusEP	0x01000000	/* instruction bus error pending */
#define DBG_MCheckP	0x00800000	/* machine check pending */
#define DBG_CacheEP	0x00400000	/* cache error pending */
#define DBG_DBusEP	0x00200000	/* data bus error pending */
#define DBG_IEXI	0x00100000	/* imprecise exception inhibit */
#define DBG_DDBSimpr	0x00080000	/* debug data break store imprecise */
#define DBG_DDBLimpr	0x00040000	/* debug data break load imprecise */
#define DBG_VERMASK	0x00038000	/* EJTAG version */
#define DBG_VERSHIFT	15
#define DBG_DEXCMASK	0x00007c00	/* latest exception code */
#define DBG_DEXCSHIFT	10
#define DBG_NoSST	0x00000200	/* no single-step */
#define DBG_SST		0x00000100	/* single-step enable */
#define DBG_DINT	0x00000020	/* debug interrupt exception */
#define DBG_DIB		0x00000010	/* debug instruction break */
#define DBG_DDBS	0x00000008	/* debug data break on store */
#define DBG_DDBL	0x00000004	/* debug data break on load */
#define DBG_DBP		0x00000002	/* debug breakpoint */
#define DBG_DSS		0x00000001	/* debug single-step */

/* Performance counter event numbers for 
   PerfCnt Registers (CP0 Register 25, Select 0 and 1) */
#define PERFCNT_EV_CYCLES	0
#define PERFCNT_EV_IFETCH_0	1
#define PERFCNT_EV_IEXEC_1	1
#define PERFCNT_EV_LOADS	2
#define PERFCNT_EV_STORES	3
#define PERFCNT_EV_CSTORES	4
#define PERFCNT_EV_FCSTORES_0	5
#define PERFCNT_EV_FPUEXEC_1	6
#define PERFCNT_EV_ITLBMISS_0	7
#define PERFCNT_EV_TLBMISS_1	7
#define PERFCNT_EV_DTLBMISS_0	8
#define PERFCNT_EV_MISPREDICT_1	8
#define PERFCNT_EV_ICMISS_0	9
#define PERFCNT_EV_DCMISS_1	9
#define PERFCNT_EV_ISCHED_0	10
#define PERFCNT_EV_ISTALL_1	10
#define PERFCNT_EV_DUAL_0	14
#define PERFCNT_EV_IEXEC_0	15
#define PERFCNT_EV_COP2EXEC_1	15

/* ErrCtl Register (CP0 Register 26, Select 0) */
#define ERRCTL_PE	0x80000000	/* parity enable */
#define ERRCTL_PO	0x40000000	/* parity overwrite */
#define ERRCTL_WST	0x20000000	/* way select / tag array */
#define ERRCTL_P	0x000000ff	/* parity bits */

/*
 * CacheErr register (CP Register 27, Select 0)
 */
#define CACHEERR_ER	        0x80000000	/* 0 = Instr, 1 = Data */
#define CACHEERR_ED		0x20000000	/* data ram error */
#define CACHEERR_ET		0x10000000	/* tag ram error */
#define CACHEERR_EB		0x02000000	/* both i & d cache error */
#define CACHEERR_EF		0x01000000	/* fatal error */
#define CACHEERR_EW		0x00400000	/* way selection error */
#define CACHEERR_IDX_MASK	0x0000ffff	/* cache index */
#define CACHEERR_IDX_SHIFT	0

/* MIPS SDE historical names */
#define CACHEERR_TYPE		CACHEERR_ER
#define CACHEERR_LEVEL		0		/* cache level */
#define CACHEERR_DATA		CACHEERR_ED
#define CACHEERR_TAG		CACHEERR_ET
#define CACHEERR_MISS		0		/* error on cache miss */
#define CACHEERR_BUS		0		/* bus error */
#define CACHEERR_BOTH		CACHEERR_EB

#ifdef __cplusplus
}
#endif
#endif /* _MIPS_OPAL_H_ */
