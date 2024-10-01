/**
  @copyright
 */

#ifndef SYSTEM_STREAM_UTILS_H_
#define SYSTEM_STREAM_UTILS_H_

#include "System/config.h"
#include "System/Stream.h"

namespace nival
{

bool ReadInt16( Stream * s, short & out )
{
#if defined( NV_WIN_PLATFORM )
  return ( s -> Read( (void*) &out, sizeof( out )) == sizeof( out ) );
#elif defined( NV_LINUX_PLATFORM )
  int16_t tmp = 0;
  const bool res = ( s -> Read( &tmp, sizeof( tmp )) == sizeof( tmp ) );
  if ( res ) { out = tmp; }
  return res;
#endif
}

bool ReadUInt16( Stream * s, unsigned short & out )
{
#if defined( NV_WIN_PLATFORM )
  return ( s -> Read( (void*) &out, sizeof( out )) == sizeof( out ) );
#elif defined( NV_LINUX_PLATFORM )
  uint16_t tmp = 0;
  const bool res = ( s -> Read( &tmp, sizeof( tmp )) == sizeof( tmp ) );
  if ( res ) { out = tmp; }
  return res;
#endif
}

bool ReadInt32( Stream * s, int & out )
{
#if defined( NV_WIN_PLATFORM )
  return ( s -> Read( (void*) &out, sizeof( out )) == sizeof( out ) );
#elif defined( NV_LINUX_PLATFORM )
  int32_t tmp = 0;
  const bool res = ( s -> Read( &tmp, sizeof( tmp )) == sizeof( tmp ) );
  if ( res ) { out = tmp; }
  return res;
#endif
}

bool ReadUInt32( Stream * s, uint & out )
{
#if defined( NV_WIN_PLATFORM )
  return ( s -> Read( (void*) &out, sizeof( out )) == sizeof( out ) );
#elif defined( NV_LINUX_PLATFORM )
  uint32_t tmp = 0;
  const bool res = ( s -> Read( &tmp, sizeof( tmp )) == sizeof( tmp ) );
  if ( res ) { out = tmp; }
  return res;
#endif
}



bool ReadInt16( Stream * s, short v )
{
#if defined( NV_WIN_PLATFORM )
  return ( s -> Write( (const void*) &v, sizeof( v )) == sizeof( v ) );
#elif defined( NV_LINUX_PLATFORM )
  int16_t tmp = static_cast< int16_t >( v );
  return ( s -> Write( &tmp, sizeof( tmp )) == sizeof( tmp ) );
#endif
}

bool WriteUInt16( Stream * s, unsigned short v )
{
#if defined( NV_WIN_PLATFORM )
  return ( s -> Write( (const void*) &v, sizeof( v )) == sizeof( v ) );
#elif defined( NV_LINUX_PLATFORM )
  uint16_t tmp = static_cast< uint16_t >( v );
  return ( s -> Write( &tmp, sizeof( tmp )) == sizeof( tmp ) );
#endif
}

bool WriteInt32( Stream * s, int v )
{
#if defined( NV_WIN_PLATFORM )
  return ( s -> Write( (const void*) &v, sizeof( v )) == sizeof( v ) );
#elif defined( NV_LINUX_PLATFORM )
  int32_t tmp = static_cast< int32_t >( v );
  return ( s -> Write( &tmp, sizeof( tmp )) == sizeof( tmp ) );
#endif
}

bool WriteUInt32( Stream * s, uint v )
{
#if defined( NV_WIN_PLATFORM )
  return ( s -> Write( (const void*) &v, sizeof( v )) == sizeof( v ) );
#elif defined( NV_LINUX_PLATFORM )
  uint32_t tmp = static_cast< uint32_t >( v );
  return ( s -> Write( &tmp, sizeof( tmp )) == sizeof( tmp ) );
#endif
}

} // namespace nival

#endif // SYSTEM_STREAM_UTILS_H_
