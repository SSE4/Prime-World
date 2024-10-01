#ifndef _SYNC_PROCESSOR_STATE_H_
#define _SYNC_PROCESSOR_STATE_H_

// FIXME : might be not suitable for x64, precision control is not supported
static const DWORD LOGIC_PROCESSOR_STATE = _EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW | _EM_UNDERFLOW | _EM_INEXACT | _EM_DENORMAL | _PC_24	| _RC_NEAR;
static const DWORD UI_PROCESSOR_STATE = _EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW | _EM_UNDERFLOW | _EM_INEXACT | _EM_DENORMAL | _PC_64	| _RC_NEAR;

void SyncProcessorState();
unsigned int GetProcessorState();
void SetProcessorState( unsigned int newState, unsigned int mask = 0xffffffff );
bool IsProcessorStateForLogic();
bool IsProcessorStateForUI();


#if !defined( NI_PLATF_LINUX )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NI_SYNC_FPU_START   \
  unsigned nFPUStatus;          \
  _controlfp_s(&nFPUStatus, 0, 0); \
  SyncProcessorState();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NI_SYNC_FPU_END     \
  unsigned unused;          \
  _controlfp_s(&unused, nFPUStatus, _MCW_EM | _MCW_RC | _MCW_PC);

#endif  // !defined( NI_PLATF_LINUX )


namespace utils
{

bool GetMemoryStatus( size_t & virtualSize );
int GetThreadCount();

} //namespace utils

#endif  // _SYNC_PROCESSOR_STATE_H_
