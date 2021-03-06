/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X16_H
#define LIBSIMDPP_SIMDPP_TYPES_INT16X16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <cstdint>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2 || SIMDPP_DOXYGEN

/// @ingroup simd_vec_int
/// @{

/** Class representing 16x 16-bit signed integer vector
*/
template<>
class int16<16, void> : public any_int16<16, int16<16,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int16_t;
    using base_vector_type = int16<16>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    int16<16>() = default;
    int16<16>(const int16<16> &) = default;
    int16<16> &operator=(const int16<16> &) = default;

    template<class E> SIMDPP_INL int16<16>(const int16<16,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL int16<16>(const uint16<16,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit int16<16>(const any_vec<32,V>& d)
    {
        *this = bit_cast<int16<16>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL int16<16>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<int16<16>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    int16<16>(const native_type& d) : d_(d) {}
    int16<16>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL int16<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int16<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int16<16>& vec(unsigned) const { return *this; }
          int16<16>& vec(unsigned)       { return *this; }
    /// @}

    int16<16> eval() const { return *this; }

    static int16<16> zero() { return detail::make_zero(); }
    static int16<16> ones() { return detail::make_ones(); }

private:
    native_type d_;
};

/** Class representing 16x 16-bit unsigned integer vector
*/
template<>
class uint16<16, void> : public any_int16<16, uint16<16,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint16_t;
    using base_vector_type = uint16<16,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    uint16<16>() = default;
    uint16<16>(const uint16<16> &) = default;
    uint16<16> &operator=(const uint16<16> &) = default;

    template<class E> SIMDPP_INL uint16<16>(const uint16<16,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL uint16<16>(const int16<16,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit uint16<16>(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint16<16>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL uint16<16>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint16<16>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    uint16<16>(const native_type& d) : d_(d) {}
    uint16<16>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL uint16<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint16<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint16<16>& vec(unsigned) const { return *this; }
          uint16<16>& vec(unsigned)       { return *this; }
    /// @}

    uint16<16> eval() const { return *this; }

    static uint16<16> zero() { return detail::make_zero(); }
    static uint16<16> ones() { return detail::make_ones(); }

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 8x 16-bit integer
/// vector
template<>
class mask_int16<16, void> : public any_int16<16, mask_int16<16,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int16<16, void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    mask_int16<16>() = default;
    mask_int16<16>(const mask_int16<16> &) = default;
    mask_int16<16> &operator=(const mask_int16<16> &) = default;

    mask_int16<16>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_AVX2
    mask_int16<16>(const uint16<16>& d) : d_(d) {}
#endif

    operator native_type() const { return d_; }

    /// Access the underlying type
    uint16<16> unmask() const
    {
    #if SIMDPP_USE_AVX2
        return uint16<16>(d_);
    #endif
    }

    const mask_int16<16>& vec(unsigned) const { return *this; }
          mask_int16<16>& vec(unsigned)       { return *this; }

    mask_int16<16> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2 || SIMDPP_DOXYGEN

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
