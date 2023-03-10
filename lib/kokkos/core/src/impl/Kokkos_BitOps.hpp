/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 3.0
//       Copyright (2020) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY NTESS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NTESS OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef KOKKOS_BITOPS_HPP
#define KOKKOS_BITOPS_HPP

#include <Kokkos_Macros.hpp>
#include <cstdint>
#include <climits>

#ifdef KOKKOS_COMPILER_INTEL
#include <immintrin.h>
#endif

namespace Kokkos {
namespace Impl {

KOKKOS_FORCEINLINE_FUNCTION
int int_log2_fallback(unsigned i) {
  constexpr int shift = sizeof(unsigned) * CHAR_BIT - 1;

  int offset = 0;
  if (i) {
    for (offset = shift; (i & (1 << offset)) == 0; --offset)
      ;
  }
  return offset;
}

KOKKOS_IMPL_DEVICE_FUNCTION
inline int int_log2_device(unsigned i) {
#if defined(KOKKOS_ENABLE_CUDA) || defined(KOKKOS_ENABLE_HIP)
  constexpr int shift = sizeof(unsigned) * CHAR_BIT - 1;
  return shift - __clz(i);
#elif defined(KOKKOS_COMPILER_INTEL)
  return _bit_scan_reverse(i);
#else
  return int_log2_fallback(i);
#endif
}

KOKKOS_IMPL_HOST_FUNCTION
inline int int_log2_host(unsigned i) {
// duplicating shift to avoid unused warning in else branch
#if defined(KOKKOS_COMPILER_INTEL)
  constexpr int shift = sizeof(unsigned) * CHAR_BIT - 1;
  (void)shift;
  return _bit_scan_reverse(i);
#elif defined(KOKKOS_COMPILER_CRAYC)
  constexpr int shift = sizeof(unsigned) * CHAR_BIT - 1;
  return i ? shift - _leadz32(i) : 0;
#elif defined(__GNUC__) || defined(__GNUG__)
  constexpr int shift = sizeof(unsigned) * CHAR_BIT - 1;
  return shift - __builtin_clz(i);
#else
  return int_log2_fallback(i);
#endif
}

#if defined(__EDG__) && !defined(KOKKOS_COMPILER_INTEL)
#pragma push
#pragma diag_suppress implicit_return_from_non_void_function
#endif
KOKKOS_FORCEINLINE_FUNCTION
int int_log2(unsigned i) {
  KOKKOS_IF_ON_DEVICE((return int_log2_device(i);))
  KOKKOS_IF_ON_HOST((return int_log2_host(i);))
}
#if defined(__EDG__) && !defined(KOKKOS_COMPILER_INTEL)
#pragma pop
#endif

/**\brief  Find first zero bit.
 *
 *  If none then return -1 ;
 */
KOKKOS_FORCEINLINE_FUNCTION
int bit_first_zero_fallback(unsigned i) noexcept {
  constexpr unsigned full = ~0u;

  int offset = -1;
  if (full != i) {
    for (offset = 0; i & (1 << offset); ++offset)
      ;
  }
  return offset;
}

KOKKOS_IMPL_DEVICE_FUNCTION
inline int bit_first_zero_device(unsigned i) noexcept {
  constexpr unsigned full = ~0u;
#if defined(KOKKOS_ENABLE_CUDA) || defined(KOKKOS_ENABLE_HIP)
  return full != i ? __ffs(~i) - 1 : -1;
#elif defined(KOKKOS_COMPILER_INTEL)
  return full != i ? _bit_scan_forward(~i) : -1;
#else
  (void)full;
  return bit_first_zero_fallback(i);
#endif
}

KOKKOS_IMPL_HOST_FUNCTION
inline int bit_first_zero_host(unsigned i) noexcept {
  constexpr unsigned full = ~0u;
#if defined(KOKKOS_COMPILER_INTEL)
  return full != i ? _bit_scan_forward(~i) : -1;
#elif defined(KOKKOS_COMPILER_CRAYC)
  return full != i ? _popcnt(i ^ (i + 1)) - 1 : -1;
#elif defined(KOKKOS_COMPILER_GNU) || defined(__GNUC__) || defined(__GNUG__)
  return full != i ? __builtin_ffs(~i) - 1 : -1;
#else
  (void)full;
  return bit_first_zero_fallback(i);
#endif
}

#if defined(__EDG__) && !defined(KOKKOS_COMPILER_INTEL)
#pragma push
#pragma diag_suppress implicit_return_from_non_void_function
#endif
KOKKOS_FORCEINLINE_FUNCTION
int bit_first_zero(unsigned i) noexcept {
  KOKKOS_IF_ON_DEVICE((return bit_first_zero_device(i);))
  KOKKOS_IF_ON_HOST((return bit_first_zero_host(i);))
}
#if defined(__EDG__) && !defined(KOKKOS_COMPILER_INTEL)
#pragma pop
#endif

KOKKOS_FORCEINLINE_FUNCTION
int bit_scan_forward_fallback(unsigned i) {
  int offset = -1;
  if (i) {
    for (offset = 0; (i & (1 << offset)) == 0; ++offset)
      ;
  }
  return offset;
}

KOKKOS_IMPL_DEVICE_FUNCTION inline int bit_scan_forward_device(unsigned i) {
#if defined(KOKKOS_ENABLE_CUDA) || defined(KOKKOS_ENABLE_HIP)
  return __ffs(i) - 1;
#elif defined(KOKKOS_COMPILER_INTEL)
  return _bit_scan_forward(i);
#else
  return bit_scan_forward_fallback(i);
#endif
}

KOKKOS_IMPL_HOST_FUNCTION inline int bit_scan_forward_host(unsigned i) {
#if defined(KOKKOS_COMPILER_INTEL)
  return _bit_scan_forward(i);
#elif defined(KOKKOS_COMPILER_CRAYC)
  return i ? _popcnt(~i & (i - 1)) : -1;
#elif defined(KOKKOS_COMPILER_GNU) || defined(__GNUC__) || defined(__GNUG__)
  return __builtin_ffs(i) - 1;
#else
  return bit_scan_forward_fallback(i);
#endif
}

#if defined(__EDG__) && !defined(KOKKOS_COMPILER_INTEL)
#pragma push
#pragma diag_suppress implicit_return_from_non_void_function
#endif
KOKKOS_FORCEINLINE_FUNCTION
int bit_scan_forward(unsigned i) {
  KOKKOS_IF_ON_DEVICE((return bit_scan_forward_device(i);))
  KOKKOS_IF_ON_HOST((return bit_scan_forward_host(i);))
}
#if defined(__EDG__) && !defined(KOKKOS_COMPILER_INTEL)
#pragma pop
#endif

/// Count the number of bits set.
KOKKOS_FORCEINLINE_FUNCTION
int bit_count_fallback(unsigned i) {
  // http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetNaive
  i = i - ((i >> 1) & ~0u / 3u);                           // temp
  i = (i & ~0u / 15u * 3u) + ((i >> 2) & ~0u / 15u * 3u);  // temp
  i = (i + (i >> 4)) & ~0u / 255u * 15u;                   // temp

  // count
  return (int)((i * (~0u / 255u)) >> (sizeof(unsigned) - 1) * CHAR_BIT);
}

KOKKOS_IMPL_DEVICE_FUNCTION inline int bit_count_device(unsigned i) {
#if defined(KOKKOS_ENABLE_CUDA) || defined(KOKKOS_ENABLE_HIP)
  return __popc(i);
#elif defined(KOKKOS_COMPILER_INTEL)
  return _popcnt32(i);
#else
  return bit_count_fallback(i);
#endif
}

KOKKOS_IMPL_HOST_FUNCTION inline int bit_count_host(unsigned i) {
#if defined(KOKKOS_COMPILER_INTEL)
  return _popcnt32(i);
#elif defined(KOKKOS_COMPILER_CRAYC)
  return _popcnt(i);
#elif defined(__GNUC__) || defined(__GNUG__)
  return __builtin_popcount(i);
#else
  return bit_count_fallback(i);
#endif
}

#if defined(__EDG__) && !defined(KOKKOS_COMPILER_INTEL)
#pragma push
#pragma diag_suppress implicit_return_from_non_void_function
#endif
KOKKOS_FORCEINLINE_FUNCTION
int bit_count(unsigned i) {
  KOKKOS_IF_ON_DEVICE((return bit_count_device(i);))
  KOKKOS_IF_ON_HOST((return bit_count_host(i);))
}
#if defined(__EDG__) && !defined(KOKKOS_COMPILER_INTEL)
#pragma pop
#endif

KOKKOS_INLINE_FUNCTION
unsigned integral_power_of_two_that_contains(const unsigned N) {
  const unsigned i = int_log2(N);
  return ((1u << i) < N) ? i + 1 : i;
}

}  // namespace Impl
}  // namespace Kokkos

#endif  // KOKKOS_BITOPS_HPP
