/* IEEE754 floating point double precision internal header file.  */
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

#ifndef __IEEE754SP__
#define __IEEE754SP__

//#include <mips/ieee/assert.h>
#include <mips/ieee/ieee754int.h>

int ieee754sp_order (ieee754sp x, ieee754sp y);

#define XSPSRS(v,rs) \
  (((rs) > (SP_MBITS+SP_GUARDBITS)) ? 1 \
   : ((v) >> (rs)) | tstlsb32(v, rs))

#define XSPSRS1(v) \
  (((v) >> 1) | ((v) & 1))

/* 3bit extended single precision sticky right shift */
#define SPXSRSXn(rs) \
  (xe += (rs), \
   xm = XSPSRS(xm, rs))

#define SPXSRSX1() \
  (xe++, xm = XSPSRS1(xm))

#define SPXSRSYn(rs) \
   (ye+=rs, \
    ym = XSPSRS(ym, rs))

#define SPXSRSY1() \
   (ye++, ym = XSPSRS1(ym))
    
#ifdef ieee754_clz

/* normalize and clear hidden bit */
#define SP_NORM_PACK(m, e, guard) \
    do { \
	int _z = ieee754_clz (m); \
        if (_z == 31) \
	  m = 0; \
	else \
	  m = (m << (_z + 1)) >> (32 - SP_MBITS - (guard)); \
	e -= _z - (32 - (1 + SP_MBITS + (guard))); \
    } while (0)

/* normalize, leaving hidden bit in place */
#define SP_NORM(m, e, guard) \
    do { \
	int _z = ieee754_clz (m); \
        _z -= 32 - (1 + SP_MBITS + (guard)); \
	m <<= _z; \
	e -= _z; \
    } while (0)

#else /* ! defined ieee754_clz */

/* normalize and clear hidden bit */
#define SP_NORM_PACK(m, e, guard) \
    do { \
      /* normalize */ \
      while ((m >> (SP_MBITS + (guard))) == 0)  \
        {m <<= 1; e--;} \
      /* clear hidden bit */ \
      m &= SP_MMASK; \
    } while (0)

/* normalize, leaving hidden bit */
#define SP_NORM(m, e, guard) \
    do { \
      while ((m >> (SP_MBITS + (guard))) == 0) \
        { m <<= 1; e--; } \
    } while (0)

#endif /* ! defined ieee754_clz */

/* convert denormal to normalized with extended exponent */
#if IEEE754_FLUSH_DENORMS > 0
#define SPDNORMx(m, e)	(void)0
#else
#define SPDNORMx(m, e)	SP_NORM(m, e, 0)
#endif
#define SPDNORMX	SPDNORMx(xm,xe)
#define SPDNORMY	SPDNORMx(ym,ye)

static __inline ieee754sp buildsp (int s, int bx, uint32_t m)
{
//    assert (((s) >> 1) == 0);
//    assert (((bx) >> SP_EBITS) == 0);
//    assert (((m) >> SP_MBITS) == 0);
    return SP_BUILD (s, bx, m);
}


#if ! IEEE754_NO_XCPT
extern ieee754sp ieee754sp_xcpt(ieee754sp, const char *, ...);
extern ieee754sp ieee754sp_nanxcpt (ieee754sp, const char *, ...);
#else
#define ieee754sp_xcpt(v, s, rest...)		v
#if IEEE754_NO_SNANS
#define ieee754sp_nanxcpt(v, s, rest...)	ieee754sp_qnan(0)
#else
#define ieee754sp_nanxcpt(v, s, rest...)	ieee754sp_snan(0)
#endif
#endif

static __inline__ int ieee754sp_isnan (ieee754sp x)
{
    return ((x << 1) 
	    > (SP_BUILD (0, SP_EMAX+1+SP_EBIAS, 0) << 1));
}

static __inline__ int ieee754sp_issnan (ieee754sp x)
{
#if IEEE754_NO_SNANS
    return 0;
#else
    return ((x << 1)
	    > (SP_BUILD (0, SP_EMAX+1+SP_EBIAS, 0x400000L) << 1));
#endif
}

static __inline__ int ieee754sp_isinf (ieee754sp x)
{
    return (x << 1) == (ieee754sp_inf(0) << 1);
}

static __inline__ ieee754sp ieee754sp_bestnan (ieee754sp x, ieee754sp y)
{
//    assert(ieee754sp_isnan(x) || ieee754sp_isnan(y));
#if IEEE754_NO_STICKY_NANS
    /* pick a NaN, any NaN */
    return ieee754sp_qnan (0);
#else
    /* carry some diagnostic through */
    return ((x << 1) > (y << 1)) ? x : y;
#endif
}

#if IEEE754_NO_STICKY_NANS
#define ieee754sp_samenan(x)	ieee754sp_qnan (0)
#else
#define ieee754sp_samenan(x)	(x)
#endif

#define SPNORMRET2(s,e,m,name,a0,a1) \
{ \
    ieee754sp V = ieee754sp_format(s,e,m); \
    if(TSTX()) \
      return ieee754sp_xcpt(V,name,a0,a1); \
    else \
      return V; \
}

#define SPNORMRET1(s,e,m,name,a0)  SPNORMRET2(s,e,m,name,a0,a0)

#if IEEE754_NO_FLAGS && IEEE754_FIXED_ROUNDING
static __inline__
#include <mips/ieee/ieee754spfmt.c>
#else
extern ieee754sp ieee754sp_format (int, int, uint32_t);
#endif

#endif /* __IEEE754SP__ */
