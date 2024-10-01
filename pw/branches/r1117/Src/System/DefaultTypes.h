#ifndef _DEFAULT_TYPES_H_
#define _DEFAULT_TYPES_H_

#include <cstdint>

#include "System/config.h"

#include <stdio.h>
#include <wchar.h>
#if defined( NV_WIN_PLATFORM )
#include <stdlib.h>
#endif

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char byte;

namespace ni_detail
{

  typedef unsigned char		Byte;

  typedef int8_t            SInt8;
  typedef int16_t           SInt16;
  typedef int32_t           SInt32;
  typedef int64_t           SInt64;

  typedef uint8_t           UInt8;
  typedef uint16_t          UInt16;
  typedef uint32_t          UInt32;
  typedef uint64_t          UInt64;

} //namespace detail

typedef unsigned short ushort;

#ifndef _interface
	#define _interface struct
#endif // _interface

#ifdef WIN32
	#define CCDECL __cdecl
	#define RETARG _Ret_bytecap_(_Size)
#else
	// The cdecl calling convention is native in gcc
#ifndef CCDECL
	#define CCDECL
#endif
	//In last GCC version alloc_size is "known"...
	//#define RETARG    __attribute__ ((alloc_size(1)))
	#define RETARG
#endif

#if defined( NV_WIN_PLATFORM )

	inline uint64_t wcstoi64(wchar_t const *str)
	{
		return _wcstoi64(str, NULL, 10);
	}

	inline uint64_t wcstoui64(wchar_t const *str)
	{
		return _wcstoui64(str, NULL, 10);
	}

#elif defined( NV_LINUX_PLATFORM )

	static int64_t wcstoi64(wchar_t const *str)
	{
		int64_t value = 0;
		if (swscanf(str, L"%I64i", &value) > 0)
			return value;

		return 0;
	}

	static uint64_t wcstoui64(wchar_t const *str)
	{
		uint64_t value = 0;
		if (swscanf(str, L"%I64u", &value) > 0)
			return value;

		return 0;
	}

#endif

#endif

