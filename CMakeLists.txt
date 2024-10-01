cmake_minimum_required(VERSION 3.15)

project(PrimeWorld)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCROOT "${CMAKE_CURRENT_SOURCE_DIR}/pw/branches/r1117/Src")
set(FMOD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../fmod-for-unreal")
set(ACE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../ACE_wrappers")
set(TERABIT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../Terabit")
set(DETOURS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../Detours")
set(MAYA_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../devKitBase")
set(STEAM_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../sdk")

add_library(fmod INTERFACE IMPORTED)
target_include_directories(fmod INTERFACE "${FMOD_ROOT}/FMODStudio/Source/FMODStudio/Public/FMOD")

add_library(ace INTERFACE IMPORTED)
target_include_directories(ace INTERFACE "${ACE_ROOT}")

add_library(terabit INTERFACE IMPORTED)
target_include_directories(terabit INTERFACE "${TERABIT_ROOT};${TERABIT_ROOT}/app")

add_library(detours INTERFACE IMPORTED)
target_include_directories(detours INTERFACE "${DETOURS_ROOT}/src")

add_library(maya INTERFACE IMPORTED)
target_include_directories(maya INTERFACE "${MAYA_ROOT}/include")

add_library(steam INTERFACE IMPORTED)
target_include_directories(steam INTERFACE "${STEAM_ROOT}/public")

find_package(zlib CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(wtl REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(CURL REQUIRED)

# find Windows SDK (DirectX SDK)
set(DXSDK "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")
include_directories("${DXSDK}/Include")

option(CXXCLI "build C++/CLI" OFF)

add_subdirectory(${SRCROOT}/Client) # x86 OK
add_subdirectory(${SRCROOT}/Core) # x86 OK
add_subdirectory(${SRCROOT}/NivalInput)
add_subdirectory(${SRCROOT}/libdb) # x86 OK
add_subdirectory(${SRCROOT}/MeshConverter) # x86 OK
add_subdirectory(${SRCROOT}/MayaExtension) # requires Maya SDK
add_subdirectory(${SRCROOT}/MemoryLib) # x86 OK
add_subdirectory(${SRCROOT}/PF_Core) # requires cxxtest
add_subdirectory(${SRCROOT}/PW_Client)
add_subdirectory(${SRCROOT}/PF_GameLogic) # requires boost, curl, MD4 (OpenSSL), JsonCpp
add_subdirectory(${SRCROOT}/Render)
add_subdirectory(${SRCROOT}/Scene) # x86 OK
add_subdirectory(${SRCROOT}/Scripts) # x86 OK
add_subdirectory(${SRCROOT}/ShaderCompiler) # x86 OK
add_subdirectory(${SRCROOT}/Sound) # requires fmod
add_subdirectory(${SRCROOT}/System) # Foundation - requires cxxtest, detours
add_subdirectory(${SRCROOT}/Terrain) # x86 OK
add_subdirectory(${SRCROOT}/UI) # requires Tamarin, avmplus
add_subdirectory(${SRCROOT}/PF_Minigames)
add_subdirectory(${SRCROOT}/Network) # requires OpenSSL
add_subdirectory(${SRCROOT}/Server/RPC) # x86 OK
add_subdirectory(${SRCROOT}/Server/NetworkAIO/naio) # requires ace, IOTerabit
add_subdirectory(${SRCROOT}/Server/NetworkAIO/transport) # requires ace, IOTerabit
add_subdirectory(${SRCROOT}/Server/NetworkAIO/mballocator) # requires ace, IOTerabit
add_subdirectory(${SRCROOT}/PW_Game) # x86 OK
add_subdirectory(${SRCROOT}/Game/PF/Client/GameChatClient) # x86 OK

if(CXXCLI)
  add_subdirectory(${SRCROOT}/EditorNative) # requires fmod, C++/CLI
  add_subdirectory(${SRCROOT}/FormulaBuilder) # C++/CLI
  add_subdirectory(${SRCROOT}/PF_EditorNative) # requires fmod, C++/CLI
endif()
