#ifndef _SSEMCOPY_H_
#define _SSEMCOPY_H_

#ifndef BUS_SEGMENT_SIZE
#define BUS_SEGMENT_SIZE 1024
#endif

#include <cstdint>

void CompileTimeCheck();

void GuardedSSEMemCopy(void* _pDestination, void* _pSource, uint32_t _size);

void __stdcall ssememcopy(void* _pDestination, void* _pSource, uint32_t _size);

#endif

