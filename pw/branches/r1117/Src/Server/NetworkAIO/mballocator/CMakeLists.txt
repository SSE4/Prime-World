add_library(mballocator
MessageBlock.cpp
MessageBlock.h
MessageBlockAllocator.cpp
MessageBlockAllocator.h
MessageBlockFactory.cpp
MessageBlockFactory.h
MessageBlockType.h
specific.h
stdafx.cpp
stdafx.h
Types.h
)
target_include_directories(mballocator PRIVATE
${SRCROOT}
${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(mballocator PRIVATE ace terabit)
