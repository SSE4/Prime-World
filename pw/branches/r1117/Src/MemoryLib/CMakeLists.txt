add_library(MemoryLib
stdafx.cpp
stdafx.h
malloc.c.h
nedmalloc.cpp
nedmalloc.h
memorylib.refs
NewDelete.component
newdelete.cpp
newdelete.h
NewHandler.cpp
NewHandler.h
NewHandlerDetails.h
SymAccess.cpp
SymAccess.h
UserMessage.cpp
UserMessage.h
#../Version.rc ExcludedFromBuild
)
target_include_directories(MemoryLib PRIVATE ${SRCROOT})
