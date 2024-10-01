#ifndef __WIN32HELPER_H__
#define __WIN32HELPER_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <float.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWin32Helper
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class com_ptr
{
	T *pData;

	void Assign( T *_pData ) 
  { 
    if ( _pData ) 
    { 
      DebugTrace( "ComPtr: Assign %p INC", (void*)_pData );
      _pData->AddRef(); 
    } 
    pData = _pData; 
  }

	void Free() 
  { 
    if ( pData ) 
    { 
      DebugTrace( "ComPtr: Free %p DEC", (void*)pData );
      pData->Release(); 
    }
    pData = 0; 
  }

public:
	com_ptr( T *_pData = 0 ) 
  { 
    Assign( _pData ); 
  }

	~com_ptr() 
  { 
    Free(); 
  }

	com_ptr( const com_ptr &a ) 
  { 
    Assign( a.pData ); 
  }

	com_ptr& operator=( const com_ptr &a ) 
  { 
    if ( pData == a.pData ) 
      return *this; 
    Free();
    Assign( a.pData ); 
    return *this; 
  }

	com_ptr& operator=( T *pObj ) 
  { 
    if ( pData == pObj ) 
      return *this; 
    Free(); 
    Assign( pObj ); 
    return *this; 
  }

	operator T*() const { return pData; }
	T* operator->() const { return pData; }

	T** GetAddr() 
  { 
    DebugTrace( "ComPtr: GetAddr", (void*)pData );
    Free(); 
    pData = 0; 
    return &pData; 
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CControl87Guard
{
	unsigned int nPrevState;
public:
	CControl87Guard() { nPrevState = _control87( 0, 0 ); }
	~CControl87Guard() { _control87( nPrevState, 0xffffffff ); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPrecisionControl
{
	CControl87Guard guard;
public:
	enum EPrecisionControlMode{ PCM_HIGH = _PC_64, PCM_MEDIUM = _PC_53, PCM_LOW = _PC_24 };
	CPrecisionControl( EPrecisionControlMode mode = PCM_HIGH ) { _control87( mode, _MCW_PC ); }
	void Set( EPrecisionControlMode mode ) { _control87( mode, _MCW_PC ); };
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRoundingControl
{
	CControl87Guard guard;
public:
	enum ERoundingControlMode{ RCM_NEAR = _RC_NEAR, RCM_DOWN = _RC_DOWN, RCM_UP = _RC_UP, RCM_CHOP = _RC_CHOP };
	CRoundingControl( ERoundingControlMode mode = RCM_NEAR ) { _control87( mode, _MCW_RC ); }
	void Set( ERoundingControlMode mode ) { _control87( mode, _MCW_RC ); };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DWORD CPUID_MMX_FEATURE_PRESENT = 0x00800000;
const DWORD CPUID_SSE_FEATURE_PRESENT = 0x02000000;
inline DWORD GetCPUID()
{
	int CPUInfo[4];
	__cpuidex(CPUInfo, 1, 0);
	DWORD dwRes = CPUInfo[3]; // EDX
}
#undef GET_CPUID
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
