add_library(PF_EditorNative
EditorPassabilityMask.h
EditrorPassabilityMask.cpp
EffectSceneObject.cpp
EffectSceneObject.h
EffectsPool.cpp
EffectsPool.h
GameCameraLimits.cpp
GameCameraLimits.h
stdafx.cpp
stdafx.h
TileMapHelper.cpp
TileMapHelper.h
Utils.cpp
Utils.h
WaterMap.cpp
WaterMap.h
)
target_include_directories(PF_EditorNative PRIVATE ${SRCROOT})
target_link_libraries(PF_EditorNative PRIVATE fmod)