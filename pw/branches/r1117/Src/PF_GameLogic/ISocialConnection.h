#ifndef ISOCIALCONNECTION_H_224E6AF9_413
#define ISOCIALCONNECTION_H_224E6AF9_413

#include <cstdint>

namespace NGameX
{

_interface ISocialConnection : public IBaseInterfaceST
{
  virtual bool AddFriend( int64_t auid ) = 0;
  virtual bool CreateComplaint( int64_t toauid, int category, const nstl::wstring& text, const nstl::wstring& _logs, int kills, int deaths, int assists,
                                       int points, int prime, int leave, int distance, int afks ) = 0;
  virtual bool ChoosePartyAgain(const nstl::vector<int64_t>& auids, const uint64_t sessionId, const uint64_t timeLeft, const bool agreed) = 0;
  virtual bool SendTeam(int64_t auid, const nstl::vector<int64_t>& team_auids)=0;
  virtual void Step() = 0;
  virtual void Share() = 0;
  virtual void Share( int _x, int _y, int _width, int _height ) = 0;

  virtual void OnProtectionError() = 0;

private:
    NI_DECLARE_CLASS_1( ISocialConnection, IBaseInterfaceST );
};

}

#endif //#define ISOCIALCONNECTION_H_224E6AF9_413
