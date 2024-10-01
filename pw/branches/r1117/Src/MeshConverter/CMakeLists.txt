add_library(MeshConverter
MeshLoader.h
stdafx.cpp
stdafx.h
UberHeader.h
MeshConverter.cpp
MeshHeader.h
SkeletalAnimationHeader.h
SkeletonHeader.h
)
target_include_directories(MeshConverter PRIVATE ${SRCROOT})
