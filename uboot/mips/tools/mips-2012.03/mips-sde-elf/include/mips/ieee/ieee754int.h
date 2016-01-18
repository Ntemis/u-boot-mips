/* IEEE754 floating point common internal header file.  */
/*
 * Copyright (c) 1996-2005 MIPS Technologies, Inc.
 * Copyright (c) 2009 CodeSourcery, Inc.
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

#ifndef __IEEE754INT__
#define __IEEE754INT__

#include <mips/ieee/ieee754.h>

#define DP_EBIAS	1023
#define DP_EMIN		(-1022)
#define DP_EMAX		1023
#define DP_MBITS	52
#define DP_FBITS	52
#define DP_EBITS	11
#define DP_GUARDBITS	3

#define SP_EBIAS	127
#define SP_EMIN		(-126)
#define SP_EMAX		127
#define SP_MBITS	23
#define SP_FBITS	23
#define SP_EBITS	8
#define SP_GUARDBITS	3

#define DP_MBIT(x)	(1ULL << (x))
#define DP_MMASK	(DP_MBIT(DP_MBITS)-1)
#define DP_HIDDEN_BIT	DP_MBIT(DP_MBITS)
#define DP_SIGN_BIT	DP_MBIT(DP_EBITS + DP_MBITS)
#define DP_ENORM(x)	(((unsigned int)((x) - 1)) < (DP_EBIAS + DP_EMAX))
#define DP_BUILD(s,x,m)	(((ieee754dp) \
			     (((s) << DP_EBITS) \
			      | (x)) \
			     << DP_MBITS) \
			 | (m))

#define SP_MBIT(x)	(1U << (x))
#define SP_MMASK	(SP_MBIT(SP_MBITS)-1)
#define SP_HIDDEN_BIT	SP_MBIT(SP_MBITS)
#define SP_SIGN_BIT	SP_MBIT(SP_EBITS + SP_MBITS)
#define SP_ENORM(x)	(((unsigned int)((x) - 1)) < (SP_EBIAS + SP_EMAX))
#define SP_BUILD(s,x,m)	(((ieee754sp) \
			     (((s) << SP_EBITS) \
			      | (x)) \
			     << SP_MBITS) \
			 | (m))

#define SPSIGN(sp)	({ieee754sp_u _u; _u.bits = sp; _u.parts.sign;})
#define SPBEXP(sp)	({ieee754sp_u _u; _u.bits = sp; _u.parts.bexp;})
#define SPMANT(sp)	({ieee754sp_u _u; _u.bits = sp; _u.parts.mant;})

#define DPSIGN(dp)	({ieee754dp_u _u; _u.bits = dp; _u.parts.sign;})
#define DPBEXP(dp)	({ieee754dp_u _u; _u.bits = dp; _u.parts.bexp;})
#define DPMANT(dp)	({ieee754dp_u _u; _u.bits = dp; _u.parts.mant;})

#ifdef __GNUC__
#define LIKELY(COND)	__builtin_expect ((COND), 1)
#define UNLIKELY(COND)	__builtin_expect ((COND), 0)
#else
#define LIKELY(COND)	(COND)
#define UNLIKELY(COND)	(COND)
#endif

#if IEEE754_CLASS_CASE
#define CLPAIR(x,y)	((x)*6+(y))
#else
#define CLPAIR(x,y)	((x)|(y))
#endif

#define CLPAIR_NORM_P(cp) \
    LIKELY ((cp) == CLPAIR (IEEE754_CLASS_NORM, IEEE754_CLASS_NORM))

#define CLASS_NORM_P(c) \
    LIKELY ((c) == IEEE754_CLASS_NORM)

#define CLEARCX	\
  IEEE754_ZERO_CX ()

#define SETCX(x) \
  ({IEEE754_SET_CX(x); \
    IEEE754_SET_SX(x); \
    IEEE754_TST_MX(x);})

#define TSTX()	\
  (IEEE754_GET_MX() & IEEE754_GET_CX())

#define COMPXSP \
  uint32_t xm; int xe; int xs __attribute__((unused)); int xc

#define COMPXSP_NO_XC \
  uint32_t xm; int xe; int xs;

#define COMPYSP \
  uint32_t ym; int ye; int ys; int yc; int cp


#define EXPLODESP(v,vc,vs,ve,vm) \
{\
    ieee754sp_u _u = {.bits = v}; \
    vs = _u.parts.sign;\
    ve = _u.parts.bexp;\
    vm = _u.parts.mant;\
    if (LIKELY (SP_ENORM (ve))) {\
	ve -= SP_EBIAS;\
	vm |= SP_HIDDEN_BIT;\
	vc = IEEE754_CLASS_NORM;\
    } else {\
      if(ve == SP_EMIN-1+SP_EBIAS) {\
	if(IEEE754_FLUSH_DENORMS <= 0 && UNLIKELY (vm != 0)) {\
	    ve = SP_EMIN;\
	    vc = IEEE754_CLASS_DNORM;\
	} else\
	  vc = IEEE754_CLASS_ZERO;\
      } else {\
        if(vm == 0)\
	    vc = IEEE754_CLASS_INF;\
	else if(! IEEE754_NO_SNANS && (vm & SP_MBIT(SP_MBITS-1))) \
	    vc = IEEE754_CLASS_SNAN;\
	else \
	    vc = IEEE754_CLASS_QNAN;\
      }\
    }\
}
#define EXPLODEXSP EXPLODESP(x,xc,xs,xe,xm)
#define EXPLODEYSP {EXPLODESP(y,yc,ys,ye,ym); cp = CLPAIR(xc, yc);}

#define COMPXDP \
uint64_t xm; int xe; int xs __attribute__((unused)); int xc 

#define COMPXDP_NO_XC \
uint64_t xm; int xe; int xs;

#define COMPYDP \
uint64_t ym; int ye; int ys; int yc; int cp

#define EXPLODEDP(v,vc,vs,ve,vm) \
{\
    ieee754dp_u _u = {.bits = v}; \
    vs = _u.parts.sign;\
    ve = _u.parts.bexp;\
    vm = _u.parts.mant;\
    if (LIKELY (DP_ENORM (ve))) {\
	ve -= DP_EBIAS;\
	vm |= DP_HIDDEN_BIT;\
	vc = IEEE754_CLASS_NORM;\
    } else {\
      if(ve == DP_EMIN-1+DP_EBIAS) {\
	if(IEEE754_FLUSH_DENORMS <= 0 && UNLIKELY (vm != 0)) {\
	    ve = DP_EMIN;\
	    vc = IEEE754_CLASS_DNORM;\
	} else\
	  vc = IEEE754_CLASS_ZERO;\
      } else {\
	if(vm == 0)\
	    vc = IEEE754_CLASS_INF;\
	else if(! IEEE754_NO_SNANS && (vm & DP_MBIT(DP_MBITS-1))) \
	    vc = IEEE754_CLASS_SNAN;\
	else \
	    vc = IEEE754_CLASS_QNAN;\
      }\
    }\
}
#define EXPLODEXDP EXPLODEDP(x,xc,xs,xe,xm)
#define EXPLODEYDP {EXPLODEDP(y,yc,ys,ye,ym); cp = CLPAIR(xc, yc);}

#define ieee754dp_zero(sn) \
  DP_BUILD (sn, DP_EMIN-1+DP_EBIAS, 	0x0000000000000LL)	/* +/- 0.0   */
#define ieee754dp_one(sn) \
  DP_BUILD (sn, DP_EBIAS, 		0x0000000000000LL)	/* +/- 1.0   */
#define ieee754dp_ten(sn) \
  DP_BUILD (sn, 3+DP_EBIAS, 		0x4000000000000LL)	/* +/- 10.0  */
#define ieee754dp_inf(sn) \
  DP_BUILD (sn, DP_EMAX+1+DP_EBIAS, 	0x0000000000000LL)	/* +/- Inf   */
#define ieee754dp_qnan(sn) \
  DP_BUILD (sn, DP_EMAX+1+DP_EBIAS,	0x7FFFFFFFFFFFFLL)	/* QNan      */
#define ieee754dp_snan(sn) \
  DP_BUILD (sn, DP_EMAX+1+DP_EBIAS,	0xFFFFFFFFFFFFFLL)	/* SNan      */
#define ieee754dp_max(sn) \
  DP_BUILD (sn, DP_EMAX+DP_EBIAS,	0xFFFFFFFFFFFFFLL)	/* +/- max  */
#define ieee754dp_min(sn) \
  DP_BUILD (sn, DP_EMIN+DP_EBIAS,	0x0000000000000LL)	/* +/- min normal */
#define ieee754dp_mind(sn) \
  DP_BUILD (sn, DP_EMIN-1+DP_EBIAS,	0x0000000000001LL)	/* +/- min denormal */
#define ieee754dp_1e31(sn) \
  DP_BUILD (sn, 31+DP_EBIAS,		0x0000000000000LL)	/* +/- 1.0e31 */
#define ieee754dp_1e63(sn) \
  DP_BUILD (sn, 63+DP_EBIAS, 		0x0000000000000LL)	/* +/- 1.0e63 */

#define ieee754sp_zero(sn) \
  SP_BUILD (sn, SP_EMIN-1+SP_EBIAS, 	0x000000L)		/* +/- 0.0   */
#define ieee754sp_one(sn) \
  SP_BUILD (sn, SP_EBIAS, 		0x000000L)		/* +/- 1.0   */
#define ieee754sp_ten(sn) \
  SP_BUILD (sn, 3+SP_EBIAS, 		0x200000L)		/* +/- 10.0  */
#define ieee754sp_inf(sn) \
  SP_BUILD (sn, SP_EMAX+1+SP_EBIAS, 	0x000000L)		/* +/- Inf   */
#define ieee754sp_qnan(sn) \
  SP_BUILD (sn, SP_EMAX+1+SP_EBIAS,	0x3FFFFFL)		/* QNan      */
#define ieee754sp_snan(sn) \
  SP_BUILD (sn, SP_EMAX+1+SP_EBIAS,	0x7FFFFFL)		/* SNan      */
#define ieee754sp_max(sn) \
  SP_BUILD (sn, SP_EMAX+SP_EBIAS,	0x7FFFFFL)		/* +/- max  */
#define ieee754sp_min(sn) \
  SP_BUILD (sn, SP_EMIN+SP_EBIAS,	0x000000L)		/* +/- min normal */
#define ieee754sp_mind(sn) \
  SP_BUILD (sn, SP_EMIN-1+SP_EBIAS,	0x000001L)		/* +/- min denormal */
#define ieee754sp_1e31(sn) \
  SP_BUILD (sn, 31+SP_EBIAS,		0x000000L)		/* +/- 1.0e31 */
#define ieee754sp_1e63(sn) \
  SP_BUILD (sn, 63+SP_EBIAS, 		0x000000L)		/* +/- 1.0e63 */

/* indefinite values */
#define ieee754sp_indef()	ieee754sp_qnan(0)
#define ieee754dp_indef()	ieee754dp_qnan(0)
#define ieee754si_indef()	INT_MIN
#if defined(LONG_LONG_MIN)
#define ieee754di_indef()	LONG_LONG_MIN
#elif defined(LLONG_MIN)
#define ieee754di_indef()	LLONG_MIN
#else
#define ieee754di_indef()	(-0x7fffffffffffffffLL - 1)
#endif


#if ! IEEE754_NO_XCPT
extern uint32_t	ieee754si_xcpt (uint32_t, const char *, ...);
extern uint64_t	ieee754di_xcpt (uint64_t, const char *, ...);
#else
#define ieee754si_xcpt(v, s, rest...)		v
#define ieee754di_xcpt(v, s, rest...)		v
#endif

#if (__mips == 32 || __mips == 64) && !__mips16
# if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  define ieee754_clz(x) __builtin_clz (x)
#  define ieee754_ctz(x) __builtin_ctz (x)
# else
#  define ieee754_clz(x) __extension__({ \
    uint32_t __wx = (x); \
    int __v; \
    __asm__ ("clz %0,%1" : "=d" (__v) : "d" (__wx)); \
    __v; \
   })
#  define ieee754_ctz(x) (31 ^ ieee754_clz ((x) & -(x)))
# endif
# if __mips64
#  if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#   define ieee754_dclz(x) __builtin_clzll (x)
#   define ieee754_dctz(x) __builtin_ctzll (x)
#  else
#   define ieee754_dclz(x) __extension__({ \
    uint64_t __dx = (x); \
    int __v; \
    __asm__ ("dclz %0,%1" : "=d" (__v) : "d" (__dx)); \
    __v; \
    })
#   define ieee754_dctz(x) (63 ^ ieee754_dclz ((x) & -(x)))
#  endif
# else /* ! __mips64 */
#  define ieee754_dclz(x) __extension__({ \
    uint64_t __dx = (x); \
    uint32_t __hdx = (__dx >> 32); \
    __hdx ? ieee754_clz(__hdx) : (32 + ieee754_clz(__dx)); \
   })
#  define ieee754_dctz(x) __extension__({ \
    uint64_t __dx = (x); \
    uint32_t __ldx = __dx; \
    uint32_t __hdx = __dx >> 32; \
    __ldx ? ieee754_ctz(__ldx) : (63 ^ ieee754_clz(__hdx & -__hdx)); \
   })
# endif /* ! __mips64 */
#endif /* __mips == 32 || __mips == 64 */

/* return 1 if any of the least sig RS bits are non-zero */
#if __mips64
/* a shift is fast */
#define tstlsb64(v, rs) \
  (__builtin_constant_p(rs) \
   ? (((v) & ((1ULL << (rs)) - 1)) != 0) \
   : ((((v) << (64 - (rs))) != 0)))
#else
/* avoid full-blown 64-bit variable shift */
#define tstlsb64(v, rs) \
  (__builtin_constant_p(rs) \
   ? ((rs) < 32 \
      ? (((uint32_t)(v) & ((1U << (rs)) - 1)) != 0) \
      : (((v) & ((1ULL << (rs)) - 1)) != 0)) \
   : ({ \
       int __rs = /*64*/-(rs); \
       uint64_t __v = v; \
       uint32_t __b = __v; \
       if ((__rs & 32) == 0) \
	__b |= (uint32_t)(__v >> 32) << __rs; \
       else \
	 __b <<= __rs; /* XXX mask with 31? */ \
       __b != 0; \
   }))
#endif

#define tstlsb32(v, rs) \
  (__builtin_constant_p(rs) \
   ? (((v) & ((1U << (rs)) - 1)) != 0) \
   : ((((v) << (32 - (rs))) != 0)))

#if __mips_isa_rev >= 2 && !__mips16
#define clearmsb32(val, nbits) \
({ \
    uint32_t __v = (val); \
    __asm__ ("ins %0,$0,%1,%2" \
		 : "+d" (__v) \
		 : "I" (32 - (nbits)), "I" (nbits)); \
    __v; \
})
#else
#define clearmsb32(val, nbits) \
    (((val) << (nbits)) >> (nbits))
#endif

#if __mips64 && __mips_isa_rev >= 2 && !__mips16
#define clearmsb64(val, nbits) \
({ \
    uint64_t __v = (val); \
    __asm__ ("dins %0,$0,%1,%2" \
		 : "+d" (__v) \
		 : "I" (64 - (nbits)), "I" (nbits)); \
    __v; \
})
#elif __mips64
#define clearmsb64(val, nbits) \
    (((val) << (nbits)) >> (nbits))
#else
#define clearmsb64(val, nbits) \
    ((val) & ((1ULL << (64 - (nbits))) - 1))
#endif

#endif /* __IEEE754INT__ */
