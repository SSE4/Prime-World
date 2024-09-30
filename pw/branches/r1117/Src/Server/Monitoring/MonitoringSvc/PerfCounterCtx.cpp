#include "stdafx.h"
#include "PerfCounterCtx.h"

namespace Monitoring
{
  nstl::wstring const & PerfCounterCtx::val() const
  {
    return val_;
  }
}
