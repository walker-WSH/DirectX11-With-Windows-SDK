# Install script for directory: E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/DirectX11 With Windows SDK")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.2.0-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/workspace/DirectX11-With-Windows-SDK-forked/build/assimp/lib/Debug/assimp-vc142-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/workspace/DirectX11-With-Windows-SDK-forked/build/assimp/lib/Release/assimp-vc142-mt.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.2.0" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/workspace/DirectX11-With-Windows-SDK-forked/build/assimp/bin/Debug/assimp-vc142-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/workspace/DirectX11-With-Windows-SDK-forked/build/assimp/bin/Release/assimp-vc142-mt.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/anim.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/aabb.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/ai_assert.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/camera.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/color4.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/color4.inl"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/build/assimp/code/../include/assimp/config.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/ColladaMetaData.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/commonMetaData.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/defs.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/cfileio.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/light.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/material.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/material.inl"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/matrix3x3.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/matrix3x3.inl"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/matrix4x4.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/matrix4x4.inl"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/mesh.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/ObjMaterial.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/pbrmaterial.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/GltfMaterial.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/postprocess.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/quaternion.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/quaternion.inl"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/scene.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/metadata.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/texture.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/types.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/vector2.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/vector2.inl"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/vector3.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/vector3.inl"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/version.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/cimport.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/importerdesc.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Importer.hpp"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/DefaultLogger.hpp"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/ProgressHandler.hpp"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/IOStream.hpp"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/IOSystem.hpp"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Logger.hpp"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/LogStream.hpp"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/NullLogger.hpp"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/cexport.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Exporter.hpp"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/DefaultIOStream.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/DefaultIOSystem.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/SceneCombiner.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/fast_atof.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/qnan.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/BaseImporter.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Hash.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/ParsingUtils.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/StreamReader.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/StreamWriter.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/StringComparison.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/StringUtils.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/SGSpatialSort.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/GenericProperty.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/SpatialSort.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/SmallVector.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/SmoothingGroups.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/SmoothingGroups.inl"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/StandardShapes.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/RemoveComments.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Subdivision.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Vertex.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/LineSplitter.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/TinyFormatter.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Profiler.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/LogAux.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Bitmap.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/XMLTools.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/IOStreamBuffer.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/CreateAnimMesh.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/XmlParser.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/BlobIOSystem.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/MathFunctions.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Exceptional.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/ByteSwapper.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Compiler/poppack1.h"
    "E:/workspace/DirectX11-With-Windows-SDK-forked/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/workspace/DirectX11-With-Windows-SDK-forked/build/assimp/code/Debug/assimp-vc142-mt.pdb")
  endif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/workspace/DirectX11-With-Windows-SDK-forked/build/assimp/code/RelWithDebInfo/assimp-vc142-mt.pdb")
  endif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

