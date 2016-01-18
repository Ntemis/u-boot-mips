/*
 * Copyright (c) 2007 MIPS Technologies, Inc.
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
 * mips/mips34k.h : MIPS 34K family coprocessor 0 definitions
 */


#ifndef _MIPS_MIPS34K_H_
#define _MIPS_MIPS34K_H_

#ifdef __cplusplus
extern "C" {
#endif

/* MIPS32 compliant */
#include "mips/m32c0.h"

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
#define CFG0_ISP	0x01000000	/* I-side scratchpad ram */
#define CFG0_DSP	0x00800000	/* D-side scratchpad ram */
#define CFG0_UDI	0x00400000	/* UDI present */
#define CFG0_SB		0x00200000	/* SimpleBE bus mode */
#define CFG0_MM		0x00040000	/* write buffer merging enabled */
#define CFG0_BM		0x00010000	/* burst order (0 = incremental) */

/* 
 * Implementation depedent cache coherency attributes for Config0.K0 field 
 */
#define CFG_C_WTHRU_NOALLOC	0
#define CFG_C_WTHRU_ALLOC	1
#define CFG_C_UNCACHED_ACCEL	7

/*
 * Processor-specific fields in Config7 Register  (CP0 Register 16, Select 7)
 */
#define CFG7_AR		0x00010000	/* Alias Removed */
#define CFG7_ES		0x00000100	/* Externalize Sync */
#define CFG7_ULB	0x00000010	/* Uncached Loads Blocking */
#define CFG7_BP		0x00000008	/* Disable Branch Prediction */
#define CFG7_RPS	0x00000004	/* Disable Return Predicion Stack */
#define CFG7_BHT	0x00000002	/* Disable Branch History Table */
#define CFG7_SL		0x00000001	/* Disable Scheduled Loads */

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
#define DBG_DDBSimpr	0x00080000	/* debug data break imprecise */
#define DBG_DDBLimpr	0x00040000	/* debug data break imprecise */
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
#define PERFCNT_EV_ICOMPLETE	1
#define PERFCNT_EV_BRANCH_0	2
#define PERFCNT_EV_BMISS_1	2
#define PERFCNT_EV_JR31_0	3
#define PERFCNT_EV_JR31MISS_1	3
#define PERFCNT_EV_JRN31_0	4
#define PERFCNT_EV_ITLB_0	5
#define PERFCNT_EV_ITLBMISS_1	5
#define PERFCNT_EV_DTLB_0	6
#define PERFCNT_EV_DTLBMISS_1	6
#define PERFCNT_EV_JTLBI_0	7
#define PERFCNT_EV_JTLBIMISS_1	7
#define PERFCNT_EV_JTLBD_0	8
#define PERFCNT_EV_JTLBDMISS_1	8
#define PERFCNT_EV_ICACHE_0	9
#define PERFCNT_EV_ICACHEMISS_1	9
#define PERFCNT_EV_DCACHE_0	10
#define PERFCNT_EV_DCACHEWB_1	10
#define PERFCNT_EV_DCACHEMISS	11
#define PERFCNT_EV_EIV		12
#define PERFCNT_EV_EIV_DIRTY_0	13
#define PERFCNT_EV_EIV_CLEAN_1	13
#define PERFCNT_EV_INT_COMPL_0	14
#define PERFCNT_EV_FP_COMPL_1	14
#define PERFCNT_EV_LD_COMPL_0	15
#define PERFCNT_EV_ST_COMPL_1	15
#define PERFCNT_EV_J_COMPL_0	16
#define PERFCNT_EV_M16_COMPL_1	16
#define PERFCNT_EV_NOP_COMPL_0	17
#define PERFCNT_EV_MD_COMPL_1	17
#define PERFCNT_EV_STALLS_0	18
#define PERFCNT_EV_REPLAYS_1	18
#define PERFCNT_EV_SC_COMPL_0	19
#define PERFCNT_EV_SC_FAIL_1	19
#define PERFCNT_EV_PF_COMPL_0	20
#define PERFCNT_EV_PF_HIT_1	20
#define PERFCNT_EV_L2_WB_0	21
#define PERFCNT_EV_L2_ACC_1	21
#define PERFCNT_EV_L2_MISS	22
#define PERFCNT_EV_EXC_0	23
#define PERFCNT_EV_FIXUP_0	24

/* ErrCtl Register (CP0 Register 26, Select 0) */
#define ERRCTL_PE	0x80000000	/* parity enable */
#define ERRCTL_PO	0x40000000	/* parity overwrite */
#define ERRCTL_WST	0x20000000	/* way select / tag array */
#define ERRCTL_SPR	0x10000000	/* scratchpad ram select */
#define ERRCTL_PCO	0x08000000	/* precode override */
#define ERRCTL_ITC	0x04000000	/* InterThread Communication Cache inst */
#define ERRCTL_LBE	0x02000000	/* Data Bus Error load instruction */
#define ERRCTL_WABE	0x01000000	/* Data Bus Error store lost */
#define ERRCTL_L2P	0x00800000	/* L2 ECC Enable */
#define ERRCTL_PCI	0x000007e0	/* instruction precoded bits */
#define ERRCTL_PI	0x00000010	/* parity bits (insn) */
#define ERRCTL_PD	0x0000000f	/* parity bits (data) */

/*
 * CacheErr register (CP Register 27, Select 0)
 */
#define CACHEERR_ER	        0x80000000	/* 0 = Instr, 1 = Data */
#define CACHEERR_EC		0x40000000	/* non-primary cache */
#define CACHEERR_ED		0x20000000	/* data ram error */
#define CACHEERR_ET		0x10000000	/* tag ram error */
#define CACHEERR_ES		0x08000000	/* error source: 1=external */
#define CACHEERR_EE		0x04000000	/* bus error */
#define CACHEERR_EB		0x02000000	/* both i & d cache error */
#define CACHEERR_EF		0x01000000	/* fatal error */
#define CACHEERR_EW		0x00400000	/* way selection error */
#define CACHEERR_IDX_MASK	0x0000ffff	/* cache index */
#define CACHEERR_IDX_SHIFT	0

/* MIPS SDE historical names */
#define CACHEERR_TYPE		CACHEERR_ER
#define CACHEERR_LEVEL		CACHEERR_EC	/* cache level */
#define CACHEERR_DATA		CACHEERR_ED
#define CACHEERR_TAG		CACHEERR_ET
#define CACHEERR_MISS		0		/* error on cache miss */
#define CACHEERR_BUS		CACHEERR_EE	/* bus error */
#define CACHEERR_BOTH		CACHEERR_EB

/* 
 * Primary Cache TagLo (CP0 Register 28, Select 0/2/4)
 */
#define TAG_SPRAM_EN		0x00000080	/* spram enable */

/* CPU-specific CACHE instruction opcodes */
#define Index_Store_Data_I      0x0c        	/* 3       0 */
#define Index_Store_Data_D      0x0d        	/* 3       1 */

/* FIR - FPU Implementation Register */
#define FPA_FIR_FC		0x01000000	/* implements full cvt range */

/* FCSR - FPU Control & Status Register */
#define FPA_CSR_FN		0x00200000	/* flush to nearest */
#define FPA_CSR_FO		0x00400000	/* flush override */

#ifdef __cplusplus
}
#endif
#endif /* _MIPS_MIPS34K_H_ */
