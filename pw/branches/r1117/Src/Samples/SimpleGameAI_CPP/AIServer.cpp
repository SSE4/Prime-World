#include "stdafx.h"

#include "AIServer.h"
#include "AIGameObject.h"
#include "../SimpleGame/RLocationServer.auto.h"

namespace AI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AIServer::AIServer( Transport::ITransportSystem* _transport, const Transport::TServiceId& serviceId )
{
  gateKeeper = new rpc::GateKeeper( _transport, serviceId, Transport::autoAssignClientId, this );

  rpc::Node* locationNode = gateKeeper->RequestNode( "location/0"/*Protocol::locationServerId*/ ); 
  locationNode->Query<Location::RLocationServer>( Protocol::LOCATION_SERVER_RPC_NAME, this, &AIServer::OnLocationServerReceived );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AIServer::~AIServer()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AIServer::OnLocationServerReceived( Location::RLocationServer* _locationServer )
{
  _locationServer->GetNPC( this, &AIServer::OnGetNPC );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AIServer::OnGetNPC( const nstl::vector<int>& result )
{
  npс = result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AIServer::OnDestroyContents()
{
  gateKeeper->GetGate().UnregisterFactory<Location::GameObject>();  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AIServer::OnNewNode( Transport::IChannel* channel,  rpc::Node* node )
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AIServer::OnChannelClosed( Transport::IChannel* channel,  rpc::Node* node )
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AIServer::OnCorruptData( Transport::IChannel* channel, rpc::Node* node )
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AIServer::Step( float dt, NHPTimer::STime serverTime )
{
  gateKeeper->Poll();
}

} // namespace AI
