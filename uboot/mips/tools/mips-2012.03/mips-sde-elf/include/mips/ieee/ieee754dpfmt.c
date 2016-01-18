/*
 * Copyright (c) 2009 CodeSourcery, Inc.
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
ieee754dp
ieee754dp_format(int sn, int xe, uint64_t xm)
{
  xe += DP_EBIAS;

  if (UNLIKELY (xe < DP_EBIAS + DP_EMIN))
    {
      /* Strip lower bits.  */
      int es;
	
      if (IEEE754_NO_DENORMS ())
	{
	  SETCX(IEEE754_UNDERFLOW);
	  return ieee754dp_zero(sn);
	}

       /* Sticky right shift es bits.  */
       es = DP_EBIAS + DP_EMIN - xe;
       xm = XDPSRS(xm,es);
       xe += es;

    }

  if ((uint32_t)xm & ((1 << DP_GUARDBITS) - 1))
    {
      SETCX(IEEE754_INEXACT);
      /* Inexact, must round off guard bits.  */
      switch (IEEE754_GET_RM ())
	{
	case IEEE754_RZ:
	  break;
	case IEEE754_RN:
	  xm += ((0x1 << (DP_GUARDBITS - 1)) - 1)
	          + (((uint32_t)xm >> DP_GUARDBITS) & 1);
	  break;
	case IEEE754_RU:	/* toward +Infinity */
	  if (!sn)
	    xm += (0x1 << DP_GUARDBITS);
	  break;
	case IEEE754_RD:	/* toward -Infinity */
	  if (sn) 
	    xm += (0x1 << DP_GUARDBITS);
	    break;
	}

      /* Adjust exponent for rounding overflow.  */
      if (xm & DP_MBIT(DP_MBITS + DP_GUARDBITS + 1))
	{
	  xm >>= 1;
	  xe++;
	}
    }

  /* Strip grs bits.  */
  xm >>= DP_GUARDBITS;
    
  if (UNLIKELY (xe > DP_EBIAS + DP_EMAX))
    {
       SETCX(IEEE754_OVERFLOW);
       /* -O can be table indexed by (rm,sn).  */
       switch (IEEE754_GET_RM ())
	{
	case IEEE754_RN:
	  return ieee754dp_inf (sn);
	case IEEE754_RZ:
	  return ieee754dp_max(sn);
	case IEEE754_RU:	/* toward +Infinity */
	  if (sn == 0)
	    return ieee754dp_inf (0);
	  else
	    return ieee754dp_max (1);
	case IEEE754_RD:	/* toward -Infinity */
	  if (sn == 0)
	    return ieee754dp_max (0);
	  else
	    return ieee754dp_inf (1);
	}
    }

  /* Gen norm/denorm/zero.  */
  if (UNLIKELY ((xm & DP_HIDDEN_BIT) == 0))
    {
      /* We underflow (tiny/zero).  */
      SETCX(IEEE754_UNDERFLOW);
      xe = DP_EBIAS + DP_EMIN - 1;
    } 
  else
    xm &= DP_MMASK;

  return builddp (sn, xe, xm);
}
