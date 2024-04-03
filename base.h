// common includes, types, and defines
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>
#include <stdalign.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float    f32;
typedef double   f64;
typedef size_t   usize;

#if defined(__clang__)
#define COMPILER_CLANG
#elif defined(_MSC_VER)
#define COMPILER_MSVC
#elif defined(__GNUC__)
#define COMPILER_GCC
#else
#error "Unsupported compiler."
#endif

#define ArrayCount(a) (sizeof(a) / sizeof((a)[0]))
#define Unused(x)     (void)(x)

#define Min(A, B)      (((A) < (B)) ? (A) : (B))
#define Max(A, B)      (((A) > (B)) ? (A) : (B))
#define ClampTop(A, X) Min(A, X)
#define ClampBot(X, B) Max(X, B)
#define Clamp(A, X, B) (((X) < (A)) ? (A) : ((X) > (B)) ? (B) : (X))

#define KB(n) (((u64)(n)) << 10)
#define MB(n) (((u64)(n)) << 20)
#define GB(n) (((u64)(n)) << 30)

#define mem_copy(dst, src, size) memmove((dst), (src), (size))
#define mem_set(dst, byte, size) memset((dst), (byte), (size))
#define mem_compare(a, b, size)  memcmp((a), (b), (size))
#define mem_zero(s, z)           memset((s), 0, (z))
#define mem_zero_struct(s)       mem_zero((s), sizeof(*(s)))
#define mem_zero_array(a)        mem_zero((a), sizeof(a))
