#ifndef __TYPES_H_INCLUDED__131902__
#define __TYPES_H_INCLUDED__131902__

#include "System/config.h"

#include <stddef.h>
#include <stdint.h>

namespace nival {

	typedef unsigned int		uint_t;
	typedef unsigned long		ulong_t;
	typedef unsigned char		uchar_t;
	typedef unsigned char		byte_t;

	typedef char *				str_t;
	typedef char const *		cstr_t;

	typedef wchar_t *			wstr_t;
	typedef wchar_t const *		cwstr_t;

	typedef int 				result_t;

	const result_t result_ok				= 0;

	const result_t result_false				= 1;
	const result_t result_already_done		= 2;

	const result_t result_fail				= -1;
	const result_t result_inv_args			= -2;
	const result_t result_wrong_state		= -3;
	const result_t result_no_resources		= -4;
	const result_t result_not_impl			= -5;
	const result_t result_impossible_action	= -6;

	inline bool NV_CSUCCESS( result_t checking_result )
	{
		return 0 <= checking_result;
	}

	inline bool NV_CFAIL( result_t checking_result )
	{
		return 0 > checking_result;
	}

	#define NV_CRR( __checking_struct ) \
		{ \
			result_t __check_result = ( __checking_struct ); \
			if ( NV_CFAIL( __check_result ) ) return __check_result; \
		}

} // namespace nival

#endif // __TYPES_H_INCLUDED__131902__

