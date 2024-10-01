#include "stdafx.h"
#include "Relay/RelayBalancer/RelayBalancerSvc.h"
#include "Relay/RelayBalancer/LRelayBalancerIface.auto.h"
#include "Relay/RelayBalancer/RelayBalancerNaming.h"
#include "Relay/RelayBalancer/LRelayBalancerClientNotifyIface.auto.h"
#include "Coordinator/LServiceAppearanceNotifierIface.auto.h"


namespace Relay
{

namespace Balancer
{

Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams ),
reloadCfgFlag_(false)
{
  settings_.dump();

  RegisterBackendAttach<Coordinator::IServiceAppearanceSubscriber, Coordinator::LIServiceAppearanceSubscriber>();

  impl = new BalancerImpl( settings_, BackendGk(), CoordClient()->GetFrontendAddressTranslator() );
  RegisterBackendObject<IBalancer>( impl, Balancer::ServiceRpcIface );

  RegisterBackendAttach<Relay::IBalancer, Relay::LIBalancer>();
  RegisterBackendAttach<Relay::IOutgoingClientNotifySink, Relay::LIOutgoingClientNotifySink>();
}



Service::~Service()
{
  UnregisterBackendObject<IBalancer>( impl );

  impl = 0;
}



void Service::Poll( timer::Time _now )
{
  if (reloadCfgFlag_)
  {
    settings_.dump("Previous settings", "Previous settings");
    settings_ = Settings();
    settings_.dump("  New settings   ", "  New settings   ");
    reloadCfgFlag_ = false;
  }

  impl->Step();
}



void Service::OnConfigReload()
{
  LOG_M(RBLOG).Trace("%s", __FUNCTION__);
  reloadCfgFlag_ = true;
}

} //namespace Balancer

} //namespace Relay
