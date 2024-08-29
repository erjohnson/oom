# Errors & Compilers

Random notes from [Mārtiņš Možeiko's session at Handmade Boston 2023](https://vimeo.com/855891054)

## compiler warnings

- `-Wfloat-conversion`
- `-Wreturn-stack-address`
- `-Wshadow`
- `-Wconversion`
- `-Wformat`
- `-Wduplicated-cond`
- `nodiscard`
- `-Wduplicated-branches`
- `-Wlogical-op`
- `-Wrestrict`
- `-Wnull-dereference`
- `-Wuseless-cast`
- `-Wjump-misses-init`
- `-Wdouble-promotion`

### enable

msvc: `/W3 /WX /analyze`
gcc/clang: `-Wall -Wextra -Werror`

msvc: `/W4 /Wall`

gcc/clang: `-Weverything`

http://kristerw.blogspot.com/2017/09/useful-gcc-warning-options-not-enabled.html

### disable

`-Wunused-function`

disable SLPVectorize?: `-fno-slp-vectorize`

## address sanitizer

- `-fsanitize=address`

https://github.com/google/sanitizers/wiki/AddressSanitizerManualPoisoning

```c
// Marks memory region [addr, addr+size) as unaddressable.
// This memory must be previously allocated by the user program. Accessing
// addresses in this region from instrumented code is forbidden until
// this region is unpoisoned. This function is not guaranteed to poison
// the whole region - it may poison only subregion of [addr, addr+size) due
// to ASan alignment restrictions.
// Method is NOT thread-safe in the sense that no two threads can
// (un)poison memory in the same memory region simultaneously.
void __asan_poison_memory_region(void const volatile *addr, size_t size);
// Marks memory region [addr, addr+size) as addressable.
// This memory must be previously allocated by the user program. Accessing
// addresses in this region is allowed until this region is poisoned again.
// This function may unpoison a superregion of [addr, addr+size) due to
// ASan alignment restrictions.
// Method is NOT thread-safe in the sense that no two threads can
// (un)poison memory in the same memory region simultaneously.
void __asan_unpoison_memory_region(void const volatile *addr, size_t size);

// User code should use macros instead of functions.
#if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#define ASAN_POISON_MEMORY_REGION(addr, size) \
  __asan_poison_memory_region((addr), (size))
#define ASAN_UNPOISON_MEMORY_REGION(addr, size) \
  __asan_unpoison_memory_region((addr), (size))
#else
#define ASAN_POISON_MEMORY_REGION(addr, size) \
  ((void)(addr), (void)(size))
#define ASAN_UNPOISON_MEMORY_REGION(addr, size) \
  ((void)(addr), (void)(size))
#endif 
```

## other sanitizers

- memory sanitizer
- undefined behavior
- leak sanitizer
- thread sanitizer

## other tools

dump struct layouts:

- `/d1reportAllClassLayout`
- `-fdump-record-layout`

profile compiler performance:

- `/d1reportTime`
- `-ftime-trace`

clang-query

## string formatting

```c
// gcc/clang
void log(int level, const char* msg, ...) __attribute__((format(printf, 2, 3)))

// msvc (requires /analyze compiler cli arg)
// see SAL annotations https://learn.microsoft.com/en-us/cpp/c-runtime-library/sal-annotations
void log(int level, _Printf_format_string_ const char* msg, ...);
```
