add_library(NivalInput
specific.h
stdafx.cpp
stdafx.h
Binds.cpp
Binds.h
BindsContainer.h
BindsContainerImpl.hpp
ControlsSet.cpp
ControlsSet.h
InputCommandInstance.cpp
InputCommandInstance.h
InputCommandRef.cpp
InputCommandRef.h
InputConsoleCommands.cpp
InputEvent.cpp
InputEvent.h
Section.cpp
Section.h
SystemInputEvents.cpp
SystemInputEvents.h
HwInput.cpp
HwInput.h
HwInputInterface.h
HwInputKeys.inl
#Input.component not found
#../Version.rc ExcludedFromBuild
)
target_include_directories(NivalInput PRIVATE ${SRCROOT})
