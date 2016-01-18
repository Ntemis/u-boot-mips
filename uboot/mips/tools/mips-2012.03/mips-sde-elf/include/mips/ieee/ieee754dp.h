/* IEEE754 floating point double precision internal header file */
/*
 * Copyright (c) 1996-2004 MIPS Technologies, Inc.
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

#ifndef __IEEE754DP__
#define __IEEE754DP__

//#include <mips/ieee/assert.h>
#include <mips/ieee/ieee754int.h>


int ieee754dp_order (ieee754dp x, ieee754dp y);

/* 3bit extended double precision sticky right shift */
#define XDPSRS_safe(v,rs)	\
  (((v) >> (rs)) | tstlsb64 (v, rs))

#define XDPSRS(v,rs)	\
  (((rs) > (DP_MBITS+DP_GUARDBITS)) ? 1 : XDPSRS_safe (v, rs))

#define XDPSRSX1() \
  (xe++, (xm = (xm >> 1) | (xm & 1)))

#define XDPSRS1(v)	\
  (((v) >> 1) | ((v) & 1))

#ifdef ieee754_dclz

/* normalize and clear hidden bit */
#define DP_NORM_PACK(m, e, guard) \
    do { \
	int _z = ieee754_dclz (m); \
        if (_z == 63) \
	  m = 0; \
	else \
	  m = (m << (_z + 1)) >> (64 - DP_MBITS); \
	e -= _z - (64 - (1 + DP_MBITS + (guard))); \
    } while (0)

/* normalize, leaving hidden bit and guard bits in place */
#define DP_NORM(m, e, guard) \
    do { \
	int _z = ieee754_dclz (m); \
        _z -= 64 - (1 + DP_MBITS + (guard)); \
	if (_z != 0) { \
	  m <<= _z; \
	  e -= _z; \
	} \
    } while (0)

#else /* ! defined ieee754_dclz */

/* normalize and clear hidden bit */
#define DP_NORM_PACK(m, e, guard) \
    do { \
      /* normalize */ \
      while ((m >> (DP_MBITS + (guard))) == 0)  \
        {m <<= 1; e--;} \
      /* clear hidden bit */ \
      m &= DP_MMASK; \
    } while (0)

/* normalize, leaving hidden bit */
#define DP_NORM(m, e, guard) \
  do { \
    while ((m >> (DP_MBITS + (guard))) == 0) \
      { m <<= 1; e--; } \
  } while (0)

#endif /* ! defined ieee754_dclz */

/* convert denormal to normalized with extended exponent */

#if IEEE754_FLUSH_DENORMS > 0
#define DPDNORMx(m, e)	(void)0
#else
#define DPDNORMx(m, e)	DP_NORM(m, e, 0)
#endif
#define DPDNORMX	DPDNORMx(xm,xe)
#define DPDNORMY	DPDNORMx(ym,ye)

static __inline ieee754dp builddp (int s, int bx, uint64_t m)
{
//    assert (((s) >> 1) == 0);
//    assert (((bx) >> DP_EBITS) == 0);
//    assert (((m) >> DP_MBITS) == 0);
    return DP_BUILD (s, bx, m);
}

#if ! IEEE754_NO_XCPT
extern ieee754dp ieee754dp_xcpt (ieee754dp, const char *, ...);
extern ieee754dp ieee754dp_nanxcpt (ieee754dp, const char *, ...);
#else
#define ieee754dp_xcpt(v, s, rest...)		v
#if IEEE754_NO_SNANS
#define ieee754dp_nanxcpt(v, s, rest...)	ieee754dp_qnan(0)
#else
#define ieee754dp_nanxcpt(v, s, rest...)	ieee754dp_snan(0)
#endif
#endif

static __inline__ int ieee754dp_isnan (ieee754dp x)
{
#if __mips64
    return ((x << 1) 
	    > (DP_BUILD (0, DP_EMAX+1+DP_EBIAS, 0) << 1));
#else
    return ((x & ~DP_SIGN_BIT)
	    > DP_BUILD (0, DP_EMAX+1+DP_EBIAS, 0));
#endif
}

static __inline__ int ieee754dp_issnan (ieee754dp x)
{
#if IEEE754_NO_SNANS
    return 0;
#elif  __mips64
    return ((x << 1)
	    > (DP_BUILD (0, DP_EMAX+1+DP_EBIAS, 0x8000000000000LL) << 1));
#else
    return ((x & ~DP_SIGN_BIT)
	    > DP_BUILD (0, DP_EMAX+1+DP_EBIAS, 0x8000000000000LL));
#endif
}

static __inline__ int ieee754dp_isinf (ieee754dp x)
{
#if __mips64
    return (x << 1) == (ieee754dp_inf(0) << 1);
#else
    return (x & ~DP_SIGN_BIT) == ieee754dp_inf(0);
#endif
}

static __inline__ ieee754dp ieee754dp_bestnan (ieee754dp x, ieee754dp y)
{
//    assert(ieee754dp_isnan(x) || ieee754dp_isnan(y));
#if IEEE754_NO_STICKY_NANS
    /* pick a NaN, any NaN */
    return ieee754dp_qnan (0);
#else
    /* carry some diagnostic through */
    return ((x << 1) > (y << 1)) ? x : y;
#endif
}

#if IEEE754_NO_STICKY_NANS
#define ieee754dp_samenan(x)	ieee754dp_qnan (0)
#else
#define ieee754dp_samenan(x)	(x)
#endif

#define DPNORMRET2(s,e,m,name,a0,a1) \
{ \
    ieee754dp V = ieee754dp_format(s,e,m); \
    if(TSTX()) \
      return ieee754dp_xcpt(V,name,a0,a1); \
    else \
      return V; \
}

#define DPNORMRET1(s,e,m,name,a0) \
  DPNORMRET2(s,e,m,name,a0,a0)

#if IEEE754_NO_FLAGS && IEEE754_FIXED_ROUNDING
static __inline__
#include <mips/ieee/ieee754dpfmt.c>
#else
extern ieee754dp ieee754dp_format (int, int, uint64_t);
#endif /* IEEE754_NO_FLAGS */

#endif /* __IEEE754DP__ */
