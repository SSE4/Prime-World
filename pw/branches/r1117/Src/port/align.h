#pragma once

// portable cross-platform alignment macro

#if defined(_MSC_VER)
  #define ALIGN(a) __declspec(align(a))
#elif defined(__GNUC__)
  #define ALIGN(a) __attribute__ ((aligned(a)))
#else
  #error "unknown compiler"
#endif
