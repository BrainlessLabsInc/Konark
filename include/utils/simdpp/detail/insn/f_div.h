/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_DIV_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_DIV_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/f_rcp_e.h>
#include <simdpp/core/f_rcp_rh.h>
#include <simdpp/detail/null/foreach.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


SIMDPP_INL float32x4 i_div(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::foreach<float32x4>(a, b, [](float a, float b){ return a / b; });
#elif SIMDPP_USE_SSE2
    return _mm_div_ps(a, b);
#elif SIMDPP_USE_NEON64
    return vdivq_f32(a, b);
#elif SIMDPP_USE_NEON_FLT_SP
    float32x4 x;
    x = rcp_e(b);
    x = rcp_rh(x, b);
    x = rcp_rh(x, b);
    return mul(a, x);
#elif SIMDPP_USE_ALTIVEC
    float32x4 x;
    x = rcp_e(b);
    x = rcp_rh(x, b);
    x = rcp_rh(x, b); // TODO: check how many approximation steps are needed
    return mul(a, x);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32x8 i_div(const float32x8& a, const float32x8& b)
{
    return _mm256_div_ps(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL float32<16> i_div(const float32<16>& a, const float32<16>& b)
{
    return _mm512_div_ps(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
float32<N> i_div(const float32<N>& a, const float32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_div, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL float64x2 i_div(const float64x2& a, const float64x2& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::foreach<float64x2>(a, b, [](double a, double b){ return a / b; });
#elif SIMDPP_USE_SSE2
    return _mm_div_pd(a, b);
#elif SIMDPP_USE_NEON64
    return vdivq_f64(a, b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64x4 i_div(const float64x4& a, const float64x4& b)
{
    return _mm256_div_pd(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL float64<8> i_div(const float64<8>& a, const float64<8>& b)
{
    return _mm512_div_pd(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
float64<N> i_div(const float64<N>& a, const float64<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_div, a, b);
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

