/* Copyright (c) 2009 CodeSourcery, Inc.
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of CodeSourcery nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY CODESOURCERY, INC. ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL CODESOURCERY BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define IEEE754_GCCSOFTFLOAT	1	/* use GCC softfloat interface */
#define IEEE754_NO_XCPT		1	/* disable exception handling */
#define IEEE754_NO_FLAGS	1	/* disable IEEE flag bits */
#define IEEE754_NO_SNANS	1	/* disable SNaN handling */
#define IEEE754_NO_STICKY_NANS	1	/* disable NaN propagation */
#define IEEE754_FIXED_ROUNDING	1	/* fixed round-nearest mode */

#define ieee754dp_add	__adddf3
#define ieee754dp_sub	__subdf3
#define ieee754dp_mul	__muldf3
#define ieee754dp_div	__divdf3
#define ieee754dp_neg	__negdf2
#define ieee754dp_abs	__absdf2
#define ieee754dp_nsqrt	__sqrtdf2
#define ieee754dp_order	__cmpdf2

#define ieee754dp_tint	__fixdfsi
#define ieee754dp_tlong	__fixdfdi
#define ieee754dp_tuns	__fixunsdfsi
#define ieee754dp_tulong __fixunsdfdi
#define ieee754dp_fint	__floatsidf
#define ieee754dp_funs	__floatunsidf
#define ieee754dp_flong	__floatdidf
#define ieee754dp_fulong __floatundidf

#define ieee754sp_add	__addsf3
#define ieee754sp_sub	__subsf3
#define ieee754sp_mul	__mulsf3
#define ieee754sp_div	__divsf3
#define ieee754sp_neg	__negsf2
#define ieee754sp_abs	__abssf2
#define ieee754sp_nsqrt	__sqrtsf2
#define ieee754sp_order	__cmpsf2

#define ieee754sp_tint	__fixsfsi
#define ieee754sp_tlong	__fixsfdi
#define ieee754sp_tuns	__fixunssfsi
#define ieee754sp_tulong __fixunssfdi
#define ieee754sp_fint	__floatsisf
#define ieee754sp_funs	__floatunsisf
#define ieee754sp_flong	__floatdisf
#define ieee754sp_fulong __floatundisf

#define ieee754dp_fsp	__extendsfdf2
#define ieee754sp_fdp	__truncdfsf2

#define ieee754dp_nldexp	__ldexp
#define ieee754dp_nfrexp	__frexp
#define ieee754dp_nmodf		__modf
#define ieee754dp_nfstr		__strtod

#define ieee754sp_nldexp	__ldexpf
#define ieee754sp_nfstr		__strtof
