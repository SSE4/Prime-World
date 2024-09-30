#pragma once

#include <System/Basic.h>
#include <Server/RPC/P2PNode.h>
#include <Server/RPC/GateKeeper.h>
#include <Server/RPC/LocalEntityFactory.h>
#include <Network/ClientTransportSystemIntf.h>
#include <Network/FreePortsFinder.h>
#include "Network/TransportTypes.h"
#include "Network/AddressTranslator.h"

#include "System/HPTimer.h"

#include "Server/ClusterAdmin/ClusterAdminSvc/ClusterAdminSvcIntf.h"
#include "Server/ClusterAdmin/ClusterAdminSvc/RClusterAdminSvcIntf.auto.h"

namespace TransportLayer
{
  class TransportModule;
}


namespace AdminConsole
{
  namespace Stage
  {
    enum
    {
      NONE,
      INVALID,
      LOGIN_STARTED,
      LOGIN_FINISHED,

      // отдельный набор стейтов для консольного ввода
      LOOP,
      WAIT,
      INPUT,
    };
  };

  namespace Result
  {
    enum 
    {
      NONE = -1,
      SUCCESS = 0,
      FAIL,
      IN_PROGRESS
    };
  };

  typedef NHPTimer::FTime Timestamp;
  #define GetTime() NHPTimer::GetScalarTime()

  class Client :  public BaseObjectMT, 
                  rpc::IGateKeeperCallback
  {
    NI_DECLARE_REFCOUNT_CLASS_2( Client, BaseObjectMT, rpc::IGateKeeperCallback );

  public:
    Client();

    Client( int localId, 
      StrongMT<Transport::ITransportSystem> clusterTransport, 
      nstl::string loginAddr
      );

    ~Client();

    int stage() const;
    int lastResult() const;

    // var update
    bool StepVarUpdate_Cluster();
  
    void OnClusterAdminPtr( ClusterAdmin::RIClusterAdmin* ptr );
    void NoConnectWarning();

    void SwitchToInput();
    bool HandleInput(); // обрабатываем консольную команду пользователя ( input_ ); если что-то не понравилось, вернуть false

  protected:
    //  rpc::IGateKeeperCallback
    virtual void OnNewNode( Transport::IChannel* channel,  rpc::Node* node );
    virtual void OnChannelClosed( Transport::IChannel* channel,  rpc::Node* node );
    virtual void OnCorruptData( Transport::IChannel* channel, rpc::Node* node );

    void NextInput(); // чистим строку ввода, выводим приглашение "CMD >"
    void PrintCompletions(); // выводим списки текущих переменных и доступных сервисов
  
    StrongMT<Network::INetworkDriver> netdriver_;
    StrongMT<TransportLayer::TransportModule> sptm_;
    StrongMT<Transport::ITransportSystem> transport_; 
    StrongMT<rpc::GateKeeper> gateKeeper_;
    rpc::LocalEntityFactory * factory_;
    rpc::Node * rpcNode_;
    Timestamp timeConnectStarted_;

    StrongMT<ClusterAdmin::RIClusterAdmin> clusterAdmin;
    nstl::string loginAddr_;

    int stage_;
    int lastresult_;
    bool bexit_;

    nstl::string input_; // user console input
    bool need_stage_reset_;  // ставится после любых изменений service/varlist, чтобы при запуске loop создать заново connect и реквестеры
  };

  inline int Client::stage() const
  {
    return stage_;
  }

  inline int Client::lastResult() const
  {
    return lastresult_;
  }

} // namespace AdminConsole
