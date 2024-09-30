#include "ChatCensorCheckOp.h"
#include "ChatUserContext.h"
#include "ChatSvcLogging.h"

namespace chat
{

//  censorship::ICensorClientCallback
void CensorCheckOp::TextCheckResult( censorship::TRequestId _reqId, censorship::TAuxId _auxId, censorship::ECheckResult::Enum _result, const wstring & _filteredText )
{
  if ( finished )
  {
    LOG_W(CHATLOG).Trace("Operation already completed (userG=%d useridL=%d)", user_->useridGlobal(), user_->useridLocal() );
    return;
  }

  if ( _result == censorship::ECheckResult::Dirty )
    filteredText = _filteredText;

  finished = true;
}

}
