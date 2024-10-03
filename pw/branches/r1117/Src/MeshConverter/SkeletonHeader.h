#pragma once

#include <cstdint>

#include "../System/staticvector.h"
#include "../System/staticstring.h"

struct MayaSkeletonHeader
{
	unsigned char signature[4];
	uint32_t boneCount;
};

struct H6SkeletonHeader
{
	unsigned char signature[4];
	uint32_t boneCount;
	uint32_t fragmentCount;
	uint32_t strSizeInBytes;
	uint32_t rpSkeletonInBytes;
};

struct SkeletonData
{
  unsigned int jointsCount;
  StaticVector< Matrix43 > invertedBindPoseBones;
  StaticVector< unsigned int > parentsIDs;
  StaticVector< StaticString > jointsNames;
  StaticVector< unsigned int > namesOrder;
};

struct SkeletonDataWrapper
{
public :
  typedef SkeletonData value_type;

public :
  SkeletonDataWrapper( value_type const *ptr ) : m_ptr( ptr ) {}
  value_type const* GetData() const { return m_ptr; }
  void SetData( value_type const* newPtr ) 
  { 
    NI_VERIFY( m_ptr->jointsCount == newPtr->jointsCount, "Wrong joints count", return );
    m_ptr = newPtr; 
  }

private :
  value_type const *m_ptr;

};