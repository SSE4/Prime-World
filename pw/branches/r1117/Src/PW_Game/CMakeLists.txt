add_library(PW_Game
PW_Game.cpp
../App.ico
../Application.manifest
../Application.rc
../ApplicationResources.h
../Version.h
../Version.rc
pw_game.refs
)
target_include_directories(PW_Game PRIVATE ${SRCROOT})
