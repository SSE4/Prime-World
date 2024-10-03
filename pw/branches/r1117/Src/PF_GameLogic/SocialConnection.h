#ifndef SOCIALCONNECTION_H_B249AEE3_6DAF
#define SOCIALCONNECTION_H_B249AEE3_6DAF

#include <cstdint>

#include "System/JobThread.h"
#include "ISocialConnection.h"

namespace NGameX
{

namespace Http
{
  struct HttpRequest;
}

namespace SocialBootstrap
{
  class Session;
}

class SocialConnection : public BaseObjectST, public ISocialConnection
{
  NI_DECLARE_REFCOUNT_CLASS_2( SocialConnection, BaseObjectST, ISocialConnection );

  int rid;

  const nstl::string serverName;
  const nstl::string uid;
  const nstl::string serverKey;
  const nstl::string serverSecret;
  
  int x, y, width, height;
  bool needCrop;

  nstl::vector<StrongMT<threading::JobThread>> sendRequestJobs;

  void GenerateRequest(Http::HttpRequest& request);
  void SendRequest(const Http::HttpRequest& request, const nstl::string& data = nstl::string());
  void parseAuids(const nstl::vector<int64_t>& auids, std::string& res );

public:
  explicit SocialConnection(const SocialBootstrap::Session& ss);
  SocialConnection( const char* _serverName, const char* _uid, const char* _serverKey, const char* _serverSecret );
  ~SocialConnection();

  virtual bool AddFriend( int64_t auid );
  virtual bool CreateComplaint( int64_t toauid, int category, const nstl::wstring& text, const nstl::wstring& _logs, int kills, int deaths, int assists,
                                       int points, int prime, int leave, int distance, int afks );
  virtual bool ChoosePartyAgain(const nstl::vector<int64_t>& auids, const uint64_t sessionId, const uint64_t timeLeft, const bool agreed);
  virtual bool SendTeam(int64_t auid, const nstl::vector<int64_t>& team_auids);
  virtual void Step();
  virtual void Share();
  virtual void Share( int _x, int _y, int _width, int _height );

  virtual void OnProtectionError();
};

class DummySocialConnection : public SocialConnection
{
  NI_DECLARE_REFCOUNT_CLASS_1( DummySocialConnection, SocialConnection );

public:
  DummySocialConnection() : SocialConnection("", "", "", "") {}

  virtual bool AddFriend( int64_t auid ) { return true; }
  virtual bool CreateComplaint( int64_t toauid, int category, const nstl::wstring& text, const nstl::wstring& _logs, int kills, int deaths, int assists,
                                       int points, int prime, int leave, int distance, int afks ) { return true; }
  virtual bool ChoosePartyAgain(const nstl::vector<int64_t>&, const uint64_t, const uint64_t, const bool) { return true; }
  virtual bool SendTeam(int64_t auid, const nstl::vector<int64_t>& team_auids){return true;};

  virtual void OnProtectionError() {}
};

}

#endif //#define SOCIALCONNECTION_H_B249AEE3_6DAF
