# Install script for directory: D:/Assimp/assimp-master/assimp-master/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.3.0-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Assimp/assimp-master/assimp-master/BUILD/lib/Debug/assimp-vc143-mtd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Assimp/assimp-master/assimp-master/BUILD/lib/Release/assimp-vc143-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Assimp/assimp-master/assimp-master/BUILD/lib/MinSizeRel/assimp-vc143-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Assimp/assimp-master/assimp-master/BUILD/lib/RelWithDebInfo/assimp-vc143-mt.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.3.0" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Assimp/assimp-master/assimp-master/BUILD/bin/Debug/assimp-vc143-mtd.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Assimp/assimp-master/assimp-master/BUILD/bin/Release/assimp-vc143-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Assimp/assimp-master/assimp-master/BUILD/bin/MinSizeRel/assimp-vc143-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Assimp/assimp-master/assimp-master/BUILD/bin/RelWithDebInfo/assimp-vc143-mt.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/anim.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/aabb.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/ai_assert.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/camera.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/color4.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/color4.inl"
    "D:/Assimp/assimp-master/assimp-master/BUILD/code/../include/assimp/config.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/ColladaMetaData.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/commonMetaData.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/defs.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/cfileio.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/light.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/material.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/material.inl"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/matrix3x3.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/matrix3x3.inl"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/matrix4x4.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/matrix4x4.inl"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/mesh.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/ObjMaterial.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/pbrmaterial.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/GltfMaterial.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/postprocess.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/quaternion.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/quaternion.inl"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/scene.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/metadata.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/texture.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/types.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/vector2.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/vector2.inl"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/vector3.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/vector3.inl"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/version.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/cimport.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/AssertHandler.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/importerdesc.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Importer.hpp"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/DefaultLogger.hpp"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/ProgressHandler.hpp"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/IOStream.hpp"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/IOSystem.hpp"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Logger.hpp"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/LogStream.hpp"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/NullLogger.hpp"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/cexport.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Exporter.hpp"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/DefaultIOStream.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/DefaultIOSystem.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/ZipArchiveIOSystem.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/SceneCombiner.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/fast_atof.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/qnan.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/BaseImporter.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Hash.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/MemoryIOWrapper.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/ParsingUtils.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/StreamReader.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/StreamWriter.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/StringComparison.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/StringUtils.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/SGSpatialSort.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/GenericProperty.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/SpatialSort.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/SkeletonMeshBuilder.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/SmallVector.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/SmoothingGroups.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/SmoothingGroups.inl"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/StandardShapes.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/RemoveComments.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Subdivision.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Vertex.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/LineSplitter.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/TinyFormatter.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Profiler.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/LogAux.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Bitmap.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/XMLTools.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/IOStreamBuffer.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/CreateAnimMesh.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/XmlParser.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/BlobIOSystem.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/MathFunctions.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Exceptional.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/ByteSwapper.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Compiler/pushpack1.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Compiler/poppack1.h"
    "D:/Assimp/assimp-master/assimp-master/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Assimp/assimp-master/assimp-master/BUILD/bin/Debug/assimp-vc143-mtd.pdb")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Assimp/assimp-master/assimp-master/BUILD/bin/Release/assimp-vc143-mt.pdb")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Assimp/assimp-master/assimp-master/BUILD/bin/MinSizeRel/assimp-vc143-mt.pdb")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Assimp/assimp-master/assimp-master/BUILD/bin/RelWithDebInfo/assimp-vc143-mt.pdb")
  endif()
endif()

