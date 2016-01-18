/*
 * Copyright (c) 1996-2006 MIPS Technologies, Inc.
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

/* ieee754.h: defines interface to IEEE-754 floating point emulation library
 
   Single and double precision fp ops are supported, but 
   it is missing extended precision.  */

#ifdef __SOFT_FLOAT
/* XXX This section should be removed when libc is modified to call the
   softfloat routines directly, e.g. ieee754dp_nmodf, ieee754dp_nsqrt,
   etc. */ 
#ifndef IEEE754_NO_XCPT
#define IEEE754_NO_XCPT		1
#endif
#ifndef IEEE754_NO_FLAGS
#define IEEE754_NO_FLAGS	1
#endif
#ifndef IEEE754_NO_SNANS
#define IEEE754_NO_SNANS	1
#endif
#ifndef IEEE754_NO_STICKY_NANS
#define IEEE754_NO_STICKY_NANS	1
#endif
#ifndef IEEE754_FIXED_ROUNDING
#define IEEE754_FIXED_ROUNDING	1
#endif
#else /* ! __SOFT_FLOAT */
/* Full-fat IEEE754 emulation */
#ifndef IEEE754_NO_XCPT
#define IEEE754_NO_XCPT		0
#endif
#ifndef IEEE754_NO_FLAGS
#define IEEE754_NO_FLAGS	0
#endif
#ifndef IEEE754_NO_SNANS
#define IEEE754_NO_SNANS	0
#endif
#ifndef IEEE754_NO_STICKY_NANS
#define IEEE754_NO_STICKY_NANS	0
#endif
#ifndef IEEE754_FIXED_ROUNDING
#define IEEE754_FIXED_ROUNDING	0
#endif
#endif

#define IEEE754_FLUSH_DENORMS	0	/* don't flush denormals */
#define IEEE754_CLASS_CASE	0	/* use case table class handling */

#ifndef _IEEE754_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _IEEE754_H_

#include <stdint.h>
#include <stdarg.h>
#if __OpenBSD__
#include <machine/types.h>
#endif
#include <machine/endian.h>

typedef uint64_t	ieee754dp;
typedef uint32_t	ieee754sp;

#if BYTE_ORDER == LITTLE_ENDIAN
typedef union _ieee754dp {
    struct {
	uint64_t	mant:52;
	uint32_t 	bexp:11;
	uint32_t	sign:1;
    } parts;
    uint64_t		bits;
    double		d;
} ieee754dp_u;

typedef union _ieee754sp {
    struct {
	uint32_t	mant:23;
	uint32_t 	bexp:8;
	uint32_t	sign:1;
    } parts;
    float		f;
    uint32_t	 	bits;
} ieee754sp_u;
#endif

#if BYTE_ORDER == BIG_ENDIAN
typedef union _ieee754dp {
    struct {
	uint32_t	sign:1;
	uint32_t	bexp:11;
	uint64_t	mant:52;
    } parts;
    double		d;
    uint64_t	 	bits;
} ieee754dp_u;

typedef union _ieee754sp {
    struct {
	uint32_t	sign:1;
	uint32_t 	bexp:8;
	uint32_t	mant:23;
    } parts;
    float	f;
    uint32_t	bits;
} ieee754sp_u;
#endif	

/*
 * Single precision (aka float)
 */
int		ieee754sp_finite (ieee754sp);
int		ieee754sp_class (ieee754sp);

ieee754sp	ieee754sp_abs (ieee754sp);
ieee754sp	ieee754sp_neg (ieee754sp);
ieee754sp 	ieee754sp_logb (ieee754sp);

/* x with sign of y */
ieee754sp 	ieee754sp_copysign (ieee754sp, ieee754sp);

ieee754sp 	ieee754sp_add (ieee754sp, ieee754sp);
ieee754sp 	ieee754sp_sub (ieee754sp, ieee754sp);
ieee754sp 	ieee754sp_mul (ieee754sp, ieee754sp);
ieee754sp	ieee754sp_div (ieee754sp, ieee754sp);

ieee754sp 	ieee754sp_fint (int32_t);
ieee754sp 	ieee754sp_funs (uint32_t);
ieee754sp 	ieee754sp_flong (int64_t);
ieee754sp 	ieee754sp_fulong (uint64_t);
ieee754sp 	ieee754sp_fdp (ieee754dp);

int32_t		ieee754sp_tint (ieee754sp);
uint32_t	ieee754sp_tuns (ieee754sp);
int64_t		ieee754sp_tlong (ieee754sp);
uint64_t	ieee754sp_tulong (ieee754sp);

/* compat */
#define ieee754sp_fix(x)	ieee754sp_tint (x)

int		ieee754sp_cmp (ieee754sp, ieee754sp, int);

/*
 * basic single precision math
 */
ieee754sp 	ieee754sp_nmodf (ieee754sp, ieee754sp *);
ieee754sp_u 	ieee754sp_modf (ieee754sp_u, ieee754sp_u *);
ieee754sp	ieee754sp_nfrexp (ieee754sp, int *);
ieee754sp_u	ieee754sp_frexp (ieee754sp_u, int *);
ieee754sp	ieee754sp_nldexp (ieee754sp, int);
ieee754sp_u	ieee754sp_ldexp (ieee754sp_u, int);

ieee754sp	ieee754sp_ceil (ieee754sp);
ieee754sp	ieee754sp_floor (ieee754sp);
ieee754sp	ieee754sp_trunc (ieee754sp);

ieee754sp	ieee754sp_nsqrt (ieee754sp);
ieee754sp_u	ieee754sp_sqrt (ieee754sp_u);

/*
 * double precision (aka double)
 */
int		ieee754dp_finite (ieee754dp);
int		ieee754dp_class (ieee754dp);

/* x with sign of y */
ieee754dp	ieee754dp_copysign (ieee754dp, ieee754dp);

ieee754dp	ieee754dp_add (ieee754dp, ieee754dp);
ieee754dp	ieee754dp_sub (ieee754dp, ieee754dp);
ieee754dp	ieee754dp_mul (ieee754dp, ieee754dp);
ieee754dp	ieee754dp_div (ieee754dp, ieee754dp);

ieee754dp	ieee754dp_abs (ieee754dp);
ieee754dp	ieee754dp_neg (ieee754dp);

/* return exponent as integer in floating point format */
ieee754dp	ieee754dp_logb (ieee754dp);

ieee754dp	ieee754dp_fint (int32_t);
ieee754dp	ieee754dp_funs (uint32_t);
ieee754dp	ieee754dp_flong (int64_t);
ieee754dp	ieee754dp_fulong (uint64_t);
ieee754dp	ieee754dp_fsp (ieee754sp);

ieee754dp 	ieee754dp_ceil (ieee754dp);
ieee754dp	ieee754dp_floor (ieee754dp);
ieee754dp 	ieee754dp_trunc (ieee754dp);

int32_t		ieee754dp_tint (ieee754dp);
uint32_t	ieee754dp_tuns (ieee754dp);
int64_t		ieee754dp_tlong (ieee754dp);
uint64_t	ieee754dp_tulong (ieee754dp);

/* compat */
#define ieee754dp_fix(x)	ieee754dp_tint (x)

int		ieee754dp_cmp (ieee754dp, ieee754dp,int cop);

/*
 * basic double precision math
 */
ieee754dp	ieee754dp_nmodf (ieee754dp, ieee754dp *);
ieee754dp_u	ieee754dp_modf (ieee754dp_u, ieee754dp_u *);
ieee754dp	ieee754dp_nfrexp (ieee754dp, int *);
ieee754dp_u	ieee754dp_frexp (ieee754dp_u, int *);
ieee754dp	ieee754dp_nldexp (ieee754dp, int);
ieee754dp_u	ieee754dp_ldexp (ieee754dp_u, int);

ieee754dp	ieee754dp_ceil (ieee754dp);
ieee754dp	ieee754dp_floor (ieee754dp);
ieee754dp	ieee754dp_trunc (ieee754dp);

ieee754dp	ieee754dp_nsqrt (ieee754dp);
ieee754dp_u	ieee754dp_sqrt (ieee754dp_u);



/* 6 types of floating point number */
#if IEEE754_CLASS_CASE
#define IEEE754_CLASS_NORM	0x00
#define IEEE754_CLASS_ZERO	0x01
#define IEEE754_CLASS_DNORM	0x02
#define IEEE754_CLASS_INF	0x03
#define IEEE754_CLASS_SNAN	0x04
#define IEEE754_CLASS_QNAN	0x05
#else
#define IEEE754_CLASS_NORM	0x00
#define IEEE754_CLASS_ZERO	0x01
#define IEEE754_CLASS_DNORM	0x02
#define IEEE754_CLASS_INF	0x04
#define IEEE754_CLASS_QNAN	0x08
#if ! IEEE754_NO_SNANS
#define IEEE754_CLASS_SNAN	0x10
#else
#define IEEE754_CLASS_SNAN	0x00
#endif
#endif

/* exception flag bits */
#define IEEE754_INEXACT			0x01
#define IEEE754_UNDERFLOW		0x02
#define IEEE754_OVERFLOW		0x04
#define IEEE754_ZERO_DIVIDE		0x08
#define IEEE754_INVALID_OPERATION	0x10

/* cmp operators */
#define IEEE754_CLT	0x01
#define IEEE754_CEQ	0x02
#define IEEE754_CGT	0x04
#define IEEE754_CUN	0x08

/* rounding modes */
#define IEEE754_RN	0	/* round to nearest */
#define IEEE754_RZ	1	/* round toward zero  */
#define IEEE754_RD	2	/* round toward -Infinity */
#define IEEE754_RU	3	/* round toward +Infinity */

/* alternative names */
#define IEEE754_RM	IEEE754_RD
#define IEEE754_RP	IEEE754_RU

/* "normal" comparisons */
static __inline int ieee754sp_eq (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CEQ);
}

static __inline int ieee754sp_ne (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CLT|IEEE754_CGT|IEEE754_CUN);
}

static __inline int ieee754sp_lt (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CLT);
}

static __inline int ieee754sp_le (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CLT|IEEE754_CEQ);
}

static __inline int ieee754sp_gt (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CGT);
}

static __inline int ieee754sp_ge (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CGT|IEEE754_CEQ);
}

static __inline int ieee754dp_eq (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CEQ);
}

static __inline int ieee754dp_ne (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CLT|IEEE754_CGT|IEEE754_CUN);
}

static __inline int ieee754dp_lt (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CLT);
}

static __inline int ieee754dp_le (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CLT|IEEE754_CEQ);
}

static __inline int ieee754dp_gt (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CGT);
}

static __inline int ieee754dp_ge (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CGT|IEEE754_CEQ);
}


/* like strtod */
ieee754dp	ieee754dp_nfstr (const char *, char **);
ieee754dp_u	ieee754dp_fstr (const char *, char **);

/* printf worker - but returns malloced string! */
char *		ieee754dp_tstr (ieee754dp /*val*/, int /*prec*/,
				int /*fmt*/, int /*af*/);


/* the floating point control & status register */
struct _ieee754_csr {
    uint32_t 	pad:13;
    uint32_t	noq:1;	/* set 1 for no quiet NaN's */
    uint32_t	nod:1;	/* set 1 for no denormalised numbers */
    uint32_t	cx:5;	/* exceptions this operation */
    uint32_t 	mx:5;	/* exception enable mask */
    uint32_t	sx:5;	/* sticky exceptions */
    uint32_t	rm:2;	/* current rounding mode */
};

typedef struct _ieee754_csr ieee754_csr_t;

#ifndef ieee754_csr
extern ieee754_csr_t	ieee754_csr;
#endif

#if 0
#define IEEE754_NO_QNANS()	(ieee754_csr.noq)
#else
#define IEEE754_NO_QNANS()	(0)
#endif

#if IEEE754_FLUSH_DENORMS > 0
#define IEEE754_NO_DENORMS()	(1)
#elif IEEE754_FLUSH_DENORMS < 0
#define IEEE754_NO_DENORMS()	(ieee754_csr.nod)
#else
#define IEEE754_NO_DENORMS()	(0)
#endif

#if IEEE754_FIXED_ROUNDING
#define IEEE754_GET_RM()	IEEE754_RN	/* round to nearest */
#define IEEE754_SET_RM(rm)	(void)0	
#else
#define IEEE754_GET_RM()	(ieee754_csr.rm)
#define IEEE754_SET_RM(m)	(void)(ieee754csr.rm = (m))
#endif

#if IEEE754_NO_FLAGS
#define IEEE754_SAVE_CSR(sv)	(void)0
#define IEEE754_RESTORE_CSR(sv)	(void)0
#define IEEE754_CLR_MX(x)	(void)0
#define IEEE754_CLR_SX(x)	(void)0
#define IEEE754_ZERO_CX()	(void)0
#define IEEE754_SET_MX(x)	(void)0
#define IEEE754_SET_SX(x)	(void)0
#define IEEE754_SET_CX(x)	(void)0
#define IEEE754_TST_MX(x)	0
#define IEEE754_TST_SX(x)	0
#define IEEE754_TST_CX(x)	0
#define IEEE754_GET_MX()	0
#define IEEE754_GET_SX()	0
#define IEEE754_GET_CX()    	0
#else
#define IEEE754_SAVE_CSR(sv)	(void)(sv = ieee754_csr)
#define IEEE754_RESTORE_CSR(sv)	(void)(ieee754_csr = sv)
#define IEEE754_CLR_MX(x)	(void)(ieee754_csr.mx &= ~(x))
#define IEEE754_CLR_SX(x)	(void)(ieee754_csr.sx &= ~(x))
#define IEEE754_ZERO_CX()	(void)(ieee754_csr.cx = 0)
#define IEEE754_SET_MX(x)	(void)(ieee754_csr.mx |= (x))
#define IEEE754_SET_SX(x)	(void)(ieee754_csr.sx |= (x))
#define IEEE754_SET_CX(x)	(void)(ieee754_csr.cx |= (x))
#define IEEE754_TST_MX(x)	(ieee754_csr.mx & (x))
#define IEEE754_TST_SX(x)	(ieee754_csr.sx & (x))
#define IEEE754_TST_CX(x)	(ieee754_csr.cx & (x))
#define IEEE754_GET_MX()  	(ieee754_csr.mx)
#define IEEE754_GET_SX()	(ieee754_csr.sx)
#define IEEE754_GET_CX()	(ieee754_csr.cx)
#endif

/* test for current exception condition */
static __inline int ieee754_cxtest (unsigned x)
{
    return IEEE754_TST_CX (x);
}

/* get sticky exceptions */
static __inline unsigned ieee754_getsx (void)
{
    return IEEE754_GET_SX ();
}

/* clear sticky conditions */
static __inline unsigned ieee754_clrsx (void)
{
    IEEE754_SET_SX (0);
    return 0;
}

/* set sticky conditions */
static __inline void ieee754_setsx (unsigned x)
{
    IEEE754_SET_SX (x);
}

/* test for sticky exception condition */
static __inline int ieee754_sxtest (unsigned x)
{
    return IEEE754_TST_SX (x);
}

/* debugging */
ieee754sp ieee754sp_dump (char *, ieee754sp);
ieee754dp ieee754dp_dump (char *, ieee754dp);

/* IEEE exception context, passed to handler */
struct ieee754xctx {
    const char 		*op;	/* operation name */
    int			rt;	/* result type */
    union {
	ieee754sp	sp;	/* single precision */
	ieee754dp	dp;	/* double precision */
	/* ieee754xp	xp; 	* extended precision */
	int32_t		si;	/* standard signed integer (32bits) */
	int64_t  	di;	/* extended signed integer (64bits) */
    } rv;			/* default result format implied by op */
    va_list		ap;
};

/* result types for xctx.rt */
#define IEEE754_RT_SP	0
#define IEEE754_RT_DP	1
#define IEEE754_RT_XP	2
#define IEEE754_RT_SI	3
#define IEEE754_RT_DI	4

extern void	ieee754_xcpt (struct ieee754xctx *);

/* Handy constants (single precision) */
ieee754sp ieee754sp_zero (int)  __attribute__ ((const));	/* +/- 0.0   */		 
ieee754sp ieee754sp_one (int)  __attribute__ ((const));		/* +/- 1.0   */		 
ieee754sp ieee754sp_ten (int)  __attribute__ ((const));		/* +/- 10.0  */		 
ieee754sp ieee754sp_inf (int)  __attribute__ ((const));		/* +/- Inf   */		 
ieee754sp ieee754sp_qnan (int)  __attribute__ ((const));	/* +/- QNan  */		 
ieee754sp ieee754sp_snan (int)  __attribute__ ((const));	/* +/- SNan  */		 
ieee754sp ieee754sp_max (int)  __attribute__ ((const)); 	/* +/- max   */		 
ieee754sp ieee754sp_min (int)  __attribute__ ((const));		/* +/- min (normal) */	 
ieee754sp ieee754sp_mind (int)  __attribute__ ((const));	/* +/- min (denormal) */ 
ieee754sp ieee754sp_1e31 (int)  __attribute__ ((const));	/* +/- 1.0e31 */	 
ieee754sp ieee754sp_1e63 (int)  __attribute__ ((const));	/* +/- 1.0e63 */         

/* Handy constants (double precision) */
ieee754dp ieee754dp_zero (int)  __attribute__ ((const));	/* +/- 0.0   */		 
ieee754dp ieee754dp_one (int)  __attribute__ ((const));		/* +/- 1.0   */		 
ieee754dp ieee754dp_ten (int)  __attribute__ ((const));		/* +/- 10.0  */		 
ieee754dp ieee754dp_inf (int)  __attribute__ ((const));		/* +/- Inf   */		 
ieee754dp ieee754dp_qnan (int)  __attribute__ ((const));	/* +/- QNan  */		 
ieee754dp ieee754dp_snan (int)  __attribute__ ((const));	/* +/- SNan  */		 
ieee754dp ieee754dp_max (int)  __attribute__ ((const));		/* +/- max   */		 
ieee754dp ieee754dp_min (int)  __attribute__ ((const));		/* +/- min (normal) */	 
ieee754dp ieee754dp_mind (int)  __attribute__ ((const));	/* +/- min (denormal) */ 
ieee754dp ieee754dp_1e31 (int)  __attribute__ ((const));	/* +/- 1.0e31 */	 
ieee754dp ieee754dp_1e63 (int)  __attribute__ ((const));	/* +/- 1.0e63 */         

#ifdef __cplusplus
}
#endif
#endif /* _IEEE754_H_ */
/*
 * Copyright (c) 1996-2006 MIPS Technologies, Inc.
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
 * ieee754.h: defines interface to IEEE-754 floating point emulation library
 *
 * Single and double precision fp ops are supported, but
 * it is missing extended precision.
 */

#ifdef __SOFT_FLOAT
/* XXX This section should be removed when libc is modified to call the
   softfloat routines directly, e.g. ieee754dp_nmodf, ieee754dp_nsqrt,
   etc. */ 
#ifndef IEEE754_NO_XCPT
#define IEEE754_NO_XCPT		1
#endif
#ifndef IEEE754_NO_FLAGS
#define IEEE754_NO_FLAGS	1
#endif
#ifndef IEEE754_NO_SNANS
#define IEEE754_NO_SNANS	1
#endif
#ifndef IEEE754_NO_STICKY_NANS
#define IEEE754_NO_STICKY_NANS	1
#endif
#ifndef IEEE754_FIXED_ROUNDING
#define IEEE754_FIXED_ROUNDING	1
#endif
#else /* ! __SOFT_FLOAT */
/* Full-fat IEEE754 emulation */
#ifndef IEEE754_NO_XCPT
#define IEEE754_NO_XCPT		0
#endif
#ifndef IEEE754_NO_FLAGS
#define IEEE754_NO_FLAGS	0
#endif
#ifndef IEEE754_NO_SNANS
#define IEEE754_NO_SNANS	0
#endif
#ifndef IEEE754_NO_STICKY_NANS
#define IEEE754_NO_STICKY_NANS	0
#endif
#ifndef IEEE754_FIXED_ROUNDING
#define IEEE754_FIXED_ROUNDING	0
#endif
#endif

#define IEEE754_FLUSH_DENORMS	0	/* don't flush denormals */
#define IEEE754_CLASS_CASE	0	/* use case table class handling */

#ifndef _IEEE754_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _IEEE754_H_

#include <stdint.h>
#include <stdarg.h>
#if #system(OpenBSD)
#include <machine/types.h>
#endif
#include <machine/endian.h>

typedef uint64_t	ieee754dp;
typedef uint32_t	ieee754sp;

#if BYTE_ORDER == LITTLE_ENDIAN
typedef union _ieee754dp {
    struct {
	uint64_t	mant:52;
	uint32_t 	bexp:11;
	uint32_t	sign:1;
    } parts;
    uint64_t		bits;
    double		d;
} ieee754dp_u;

typedef union _ieee754sp {
    struct {
	uint32_t	mant:23;
	uint32_t 	bexp:8;
	uint32_t	sign:1;
    } parts;
    float		f;
    uint32_t	 	bits;
} ieee754sp_u;
#endif

#if BYTE_ORDER == BIG_ENDIAN
typedef union _ieee754dp {
    struct {
	uint32_t	sign:1;
	uint32_t	bexp:11;
	uint64_t	mant:52;
    } parts;
    double		d;
    uint64_t	 	bits;
} ieee754dp_u;

typedef union _ieee754sp {
    struct {
	uint32_t	sign:1;
	uint32_t 	bexp:8;
	uint32_t	mant:23;
    } parts;
    float	f;
    uint32_t	bits;
} ieee754sp_u;
#endif	

/*
 * Single precision (aka float)
 */
int		ieee754sp_finite (ieee754sp);
int		ieee754sp_class (ieee754sp);

ieee754sp	ieee754sp_abs (ieee754sp);
ieee754sp	ieee754sp_neg (ieee754sp);
ieee754sp 	ieee754sp_logb (ieee754sp);

/* x with sign of y */
ieee754sp 	ieee754sp_copysign (ieee754sp, ieee754sp);

ieee754sp 	ieee754sp_add (ieee754sp, ieee754sp);
ieee754sp 	ieee754sp_sub (ieee754sp, ieee754sp);
ieee754sp 	ieee754sp_mul (ieee754sp, ieee754sp);
ieee754sp	ieee754sp_div (ieee754sp, ieee754sp);

ieee754sp 	ieee754sp_fint (int32_t);
ieee754sp 	ieee754sp_funs (uint32_t);
ieee754sp 	ieee754sp_flong (int64_t);
ieee754sp 	ieee754sp_fulong (uint64_t);
ieee754sp 	ieee754sp_fdp (ieee754dp);

int32_t		ieee754sp_tint (ieee754sp);
uint32_t	ieee754sp_tuns (ieee754sp);
int64_t		ieee754sp_tlong (ieee754sp);
uint64_t	ieee754sp_tulong (ieee754sp);

/* compat */
#define ieee754sp_fix(x)	ieee754sp_tint (x)

int		ieee754sp_cmp (ieee754sp, ieee754sp, int);

/*
 * basic single precision math
 */
ieee754sp 	ieee754sp_nmodf (ieee754sp, ieee754sp *);
ieee754sp_u 	ieee754sp_modf (ieee754sp_u, ieee754sp_u *);
ieee754sp	ieee754sp_nfrexp (ieee754sp, int *);
ieee754sp_u	ieee754sp_frexp (ieee754sp_u, int *);
ieee754sp	ieee754sp_nldexp (ieee754sp, int);
ieee754sp_u	ieee754sp_ldexp (ieee754sp_u, int);

ieee754sp	ieee754sp_ceil (ieee754sp);
ieee754sp	ieee754sp_floor (ieee754sp);
ieee754sp	ieee754sp_trunc (ieee754sp);

ieee754sp	ieee754sp_nsqrt (ieee754sp);
ieee754sp_u	ieee754sp_sqrt (ieee754sp_u);

/*
 * double precision (aka double)
 */
int		ieee754dp_finite (ieee754dp);
int		ieee754dp_class (ieee754dp);

/* x with sign of y */
ieee754dp	ieee754dp_copysign (ieee754dp, ieee754dp);

ieee754dp	ieee754dp_add (ieee754dp, ieee754dp);
ieee754dp	ieee754dp_sub (ieee754dp, ieee754dp);
ieee754dp	ieee754dp_mul (ieee754dp, ieee754dp);
ieee754dp	ieee754dp_div (ieee754dp, ieee754dp);

ieee754dp	ieee754dp_abs (ieee754dp);
ieee754dp	ieee754dp_neg (ieee754dp);

/* return exponent as integer in floating point format */
ieee754dp	ieee754dp_logb (ieee754dp);

ieee754dp	ieee754dp_fint (int32_t);
ieee754dp	ieee754dp_funs (uint32_t);
ieee754dp	ieee754dp_flong (int64_t);
ieee754dp	ieee754dp_fulong (uint64_t);
ieee754dp	ieee754dp_fsp (ieee754sp);

ieee754dp 	ieee754dp_ceil (ieee754dp);
ieee754dp	ieee754dp_floor (ieee754dp);
ieee754dp 	ieee754dp_trunc (ieee754dp);

int32_t		ieee754dp_tint (ieee754dp);
uint32_t	ieee754dp_tuns (ieee754dp);
int64_t		ieee754dp_tlong (ieee754dp);
uint64_t	ieee754dp_tulong (ieee754dp);

/* compat */
#define ieee754dp_fix(x)	ieee754dp_tint (x)

int		ieee754dp_cmp (ieee754dp, ieee754dp,int cop);

/*
 * basic double precision math
 */
ieee754dp	ieee754dp_nmodf (ieee754dp, ieee754dp *);
ieee754dp_u	ieee754dp_modf (ieee754dp_u, ieee754dp_u *);
ieee754dp	ieee754dp_nfrexp (ieee754dp, int *);
ieee754dp_u	ieee754dp_frexp (ieee754dp_u, int *);
ieee754dp	ieee754dp_nldexp (ieee754dp, int);
ieee754dp_u	ieee754dp_ldexp (ieee754dp_u, int);

ieee754dp	ieee754dp_ceil (ieee754dp);
ieee754dp	ieee754dp_floor (ieee754dp);
ieee754dp	ieee754dp_trunc (ieee754dp);

ieee754dp	ieee754dp_nsqrt (ieee754dp);
ieee754dp_u	ieee754dp_sqrt (ieee754dp_u);



/* 6 types of floating point number */
#if IEEE754_CLASS_CASE
#define IEEE754_CLASS_NORM	0x00
#define IEEE754_CLASS_ZERO	0x01
#define IEEE754_CLASS_DNORM	0x02
#define IEEE754_CLASS_INF	0x03
#define IEEE754_CLASS_SNAN	0x04
#define IEEE754_CLASS_QNAN	0x05
#else
#define IEEE754_CLASS_NORM	0x00
#define IEEE754_CLASS_ZERO	0x01
#define IEEE754_CLASS_DNORM	0x02
#define IEEE754_CLASS_INF	0x04
#define IEEE754_CLASS_QNAN	0x08
#if ! IEEE754_NO_SNANS
#define IEEE754_CLASS_SNAN	0x10
#else
#define IEEE754_CLASS_SNAN	0x00
#endif
#endif

/* exception flag bits */
#define IEEE754_INEXACT			0x01
#define IEEE754_UNDERFLOW		0x02
#define IEEE754_OVERFLOW		0x04
#define IEEE754_ZERO_DIVIDE		0x08
#define IEEE754_INVALID_OPERATION	0x10

/* cmp operators */
#define IEEE754_CLT	0x01
#define IEEE754_CEQ	0x02
#define IEEE754_CGT	0x04
#define IEEE754_CUN	0x08

/* rounding modes */
#define IEEE754_RN	0	/* round to nearest */
#define IEEE754_RZ	1	/* round toward zero  */
#define IEEE754_RD	2	/* round toward -Infinity */
#define IEEE754_RU	3	/* round toward +Infinity */

/* alternative names */
#define IEEE754_RM	IEEE754_RD
#define IEEE754_RP	IEEE754_RU

/* "normal" comparisons */
static __inline int ieee754sp_eq (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CEQ);
}

static __inline int ieee754sp_ne (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CLT|IEEE754_CGT|IEEE754_CUN);
}

static __inline int ieee754sp_lt (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CLT);
}

static __inline int ieee754sp_le (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CLT|IEEE754_CEQ);
}

static __inline int ieee754sp_gt (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CGT);
}

static __inline int ieee754sp_ge (ieee754sp x, ieee754sp y)
{
    return ieee754sp_cmp (x, y, IEEE754_CGT|IEEE754_CEQ);
}

static __inline int ieee754dp_eq (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CEQ);
}

static __inline int ieee754dp_ne (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CLT|IEEE754_CGT|IEEE754_CUN);
}

static __inline int ieee754dp_lt (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CLT);
}

static __inline int ieee754dp_le (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CLT|IEEE754_CEQ);
}

static __inline int ieee754dp_gt (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CGT);
}

static __inline int ieee754dp_ge (ieee754dp x, ieee754dp y)
{
    return ieee754dp_cmp (x, y, IEEE754_CGT|IEEE754_CEQ);
}


/* like strtod */
ieee754dp	ieee754dp_nfstr (const char *, char **);
ieee754dp_u	ieee754dp_fstr (const char *, char **);

/* printf worker - but returns malloced string! */
char *		ieee754dp_tstr (ieee754dp /*val*/, int /*prec*/,
				int /*fmt*/, int /*af*/);


/* the floating point control & status register */
struct _ieee754_csr {
    uint32_t 	pad:13;
    uint32_t	noq:1;	/* set 1 for no quiet NaN's */
    uint32_t	nod:1;	/* set 1 for no denormalised numbers */
    uint32_t	cx:5;	/* exceptions this operation */
    uint32_t 	mx:5;	/* exception enable mask */
    uint32_t	sx:5;	/* sticky exceptions */
    uint32_t	rm:2;	/* current rounding mode */
};

typedef struct _ieee754_csr ieee754_csr_t;

#ifndef ieee754_csr
extern ieee754_csr_t	ieee754_csr;
#endif

#if 0
#define IEEE754_NO_QNANS()	(ieee754_csr.noq)
#else
#define IEEE754_NO_QNANS()	(0)
#endif

#if IEEE754_FLUSH_DENORMS > 0
#define IEEE754_NO_DENORMS()	(1)
#elif IEEE754_FLUSH_DENORMS < 0
#define IEEE754_NO_DENORMS()	(ieee754_csr.nod)
#else
#define IEEE754_NO_DENORMS()	(0)
#endif

#if IEEE754_FIXED_ROUNDING
#define IEEE754_GET_RM()	IEEE754_RN	/* round to nearest */
#define IEEE754_SET_RM(rm)	(void)0	
#else
#define IEEE754_GET_RM()	(ieee754_csr.rm)
#define IEEE754_SET_RM(m)	(void)(ieee754csr.rm = (m))
#endif

#if IEEE754_NO_FLAGS
#define IEEE754_SAVE_CSR(sv)	(void)0
#define IEEE754_RESTORE_CSR(sv)	(void)0
#define IEEE754_CLR_MX(x)	(void)0
#define IEEE754_CLR_SX(x)	(void)0
#define IEEE754_ZERO_CX()	(void)0
#define IEEE754_SET_MX(x)	(void)0
#define IEEE754_SET_SX(x)	(void)0
#define IEEE754_SET_CX(x)	(void)0
#define IEEE754_TST_MX(x)	0
#define IEEE754_TST_SX(x)	0
#define IEEE754_TST_CX(x)	0
#define IEEE754_GET_MX()	0
#define IEEE754_GET_SX()	0
#define IEEE754_GET_CX()    	0
#else
#define IEEE754_SAVE_CSR(sv)	(void)(sv = ieee754_csr)
#define IEEE754_RESTORE_CSR(sv)	(void)(ieee754_csr = sv)
#define IEEE754_CLR_MX(x)	(void)(ieee754_csr.mx &= ~(x))
#define IEEE754_CLR_SX(x)	(void)(ieee754_csr.sx &= ~(x))
#define IEEE754_ZERO_CX()	(void)(ieee754_csr.cx = 0)
#define IEEE754_SET_MX(x)	(void)(ieee754_csr.mx |= (x))
#define IEEE754_SET_SX(x)	(void)(ieee754_csr.sx |= (x))
#define IEEE754_SET_CX(x)	(void)(ieee754_csr.cx |= (x))
#define IEEE754_TST_MX(x)	(ieee754_csr.mx & (x))
#define IEEE754_TST_SX(x)	(ieee754_csr.sx & (x))
#define IEEE754_TST_CX(x)	(ieee754_csr.cx & (x))
#define IEEE754_GET_MX()  	(ieee754_csr.mx)
#define IEEE754_GET_SX()	(ieee754_csr.sx)
#define IEEE754_GET_CX()	(ieee754_csr.cx)
#endif

/* test for current exception condition */
static __inline int ieee754_cxtest (unsigned x)
{
    return IEEE754_TST_CX (x);
}

/* get sticky exceptions */
static __inline unsigned ieee754_getsx (void)
{
    return IEEE754_GET_SX ();
}

/* clear sticky conditions */
static __inline unsigned ieee754_clrsx (void)
{
    IEEE754_SET_SX (0);
    return 0;
}

/* set sticky conditions */
static __inline void ieee754_setsx (unsigned x)
{
    IEEE754_SET_SX (x);
}

/* test for sticky exception condition */
static __inline int ieee754_sxtest (unsigned x)
{
    return IEEE754_TST_SX (x);
}

/* debugging */
ieee754sp ieee754sp_dump (char *, ieee754sp);
ieee754dp ieee754dp_dump (char *, ieee754dp);

/* IEEE exception context, passed to handler */
struct ieee754xctx {
    const char 		*op;	/* operation name */
    int			rt;	/* result type */
    union {
	ieee754sp	sp;	/* single precision */
	ieee754dp	dp;	/* double precision */
	/* ieee754xp	xp; 	* extended precision */
	int32_t		si;	/* standard signed integer (32bits) */
	int64_t  	di;	/* extended signed integer (64bits) */
    } rv;			/* default result format implied by op */
    va_list		ap;
};

/* result types for xctx.rt */
#define IEEE754_RT_SP	0
#define IEEE754_RT_DP	1
#define IEEE754_RT_XP	2
#define IEEE754_RT_SI	3
#define IEEE754_RT_DI	4

extern void	ieee754_xcpt (struct ieee754xctx *);

/* Handy constants (single precision) */
ieee754sp ieee754sp_zero (int)  __attribute__ ((const));	/* +/- 0.0   */		 
ieee754sp ieee754sp_one (int)  __attribute__ ((const));		/* +/- 1.0   */		 
ieee754sp ieee754sp_ten (int)  __attribute__ ((const));		/* +/- 10.0  */		 
ieee754sp ieee754sp_inf (int)  __attribute__ ((const));		/* +/- Inf   */		 
ieee754sp ieee754sp_qnan (int)  __attribute__ ((const));	/* +/- QNan  */		 
ieee754sp ieee754sp_snan (int)  __attribute__ ((const));	/* +/- SNan  */		 
ieee754sp ieee754sp_max (int)  __attribute__ ((const)); 	/* +/- max   */		 
ieee754sp ieee754sp_min (int)  __attribute__ ((const));		/* +/- min (normal) */	 
ieee754sp ieee754sp_mind (int)  __attribute__ ((const));	/* +/- min (denormal) */ 
ieee754sp ieee754sp_1e31 (int)  __attribute__ ((const));	/* +/- 1.0e31 */	 
ieee754sp ieee754sp_1e63 (int)  __attribute__ ((const));	/* +/- 1.0e63 */         

/* Handy constants (double precision) */
ieee754dp ieee754dp_zero (int)  __attribute__ ((const));	/* +/- 0.0   */		 
ieee754dp ieee754dp_one (int)  __attribute__ ((const));		/* +/- 1.0   */		 
ieee754dp ieee754dp_ten (int)  __attribute__ ((const));		/* +/- 10.0  */		 
ieee754dp ieee754dp_inf (int)  __attribute__ ((const));		/* +/- Inf   */		 
ieee754dp ieee754dp_qnan (int)  __attribute__ ((const));	/* +/- QNan  */		 
ieee754dp ieee754dp_snan (int)  __attribute__ ((const));	/* +/- SNan  */		 
ieee754dp ieee754dp_max (int)  __attribute__ ((const));		/* +/- max   */		 
ieee754dp ieee754dp_min (int)  __attribute__ ((const));		/* +/- min (normal) */	 
ieee754dp ieee754dp_mind (int)  __attribute__ ((const));	/* +/- min (denormal) */ 
ieee754dp ieee754dp_1e31 (int)  __attribute__ ((const));	/* +/- 1.0e31 */	 
ieee754dp ieee754dp_1e63 (int)  __attribute__ ((const));	/* +/- 1.0e63 */         

#ifdef __cplusplus
}
#endif
#endif /* _IEEE754_H_ */
