add_library(Sound
specific.h
stdafx.cpp
stdafx.h
DBSound.component
DBSound.cpp
DBSound.h
EventScene.cpp
EventScene.h
#Sound.component not found
SoundScene.cpp
SoundScene.h
SoundUI.cpp
SoundUI.h
all.component
sound.refs
#../Version.rc ExcludedFromBuild
)
target_include_directories(Sound PRIVATE ${SRCROOT})
target_link_libraries(Sound PRIVATE fmod)