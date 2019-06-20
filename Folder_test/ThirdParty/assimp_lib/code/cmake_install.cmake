# Install script for directory: /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/nrouzeva/.brew")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/ThirdParty/assimp_lib/code/libassimp.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/anim.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/ai_assert.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/camera.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/color4.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/color4.inl"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/ThirdParty/assimp_lib/code/../include/assimp/config.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/defs.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/Defines.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/cfileio.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/light.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/material.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/material.inl"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/matrix3x3.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/matrix3x3.inl"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/matrix4x4.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/matrix4x4.inl"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/mesh.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/postprocess.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/quaternion.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/quaternion.inl"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/scene.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/metadata.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/texture.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/types.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/vector2.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/vector2.inl"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/vector3.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/vector3.inl"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/version.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/cimport.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/importerdesc.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/Importer.hpp"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/DefaultLogger.hpp"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/ProgressHandler.hpp"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/IOStream.hpp"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/IOSystem.hpp"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/Logger.hpp"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/LogStream.hpp"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/NullLogger.hpp"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/cexport.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/Exporter.hpp"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/DefaultIOStream.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/DefaultIOSystem.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/SceneCombiner.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/Compiler/poppack1.h"
    "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/assimp_lib/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

