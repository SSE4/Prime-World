add_library(GameChatClient
all.component
../../../../Server/Chat/ChatSvc/ChatClientIfaceCallback.h
GameChatClient.cpp
GameChatClient.h
IGameChatClient.h
specific.h
stdafx.cpp
stdafx.h
 ../../../../Server/Chat/ChatSvc/LChatClientIfaceCallback.auto.cpp
 ../../../../Server/Chat/ChatSvc/LChatClientIfaceCallback.auto.h
 ../../../../Server/Chat/ChatSvc/LChatClientIfaceCallback.component
 ../../../../Server/Chat/ChatSvc/RChatClientIface.auto.cpp
 ../../../../Server/Chat/ChatSvc/RChatClientIface.auto.h
 ../../../../Server/Chat/ChatSvc/RChatClientIface.component
#../../../../Version.rc ExcludedFromBuild
)
target_include_directories(GameChatClient PRIVATE
${SRCROOT}
${SRCROOT}/Server
${SRCROOT}/Server/Chat)
