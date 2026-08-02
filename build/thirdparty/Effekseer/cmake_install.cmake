# Install script for directory: C:/dev/raylib-effekseer/thirdparty/Effekseer

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/raylib_effekseer")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer.Modules.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer.SIMD.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Base.Pre.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Base.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Effect.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Color.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.DefaultFile.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.File.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Manager.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.ExternalModel.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Math.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Matrix43.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Matrix44.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Resource.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.RectF.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Setting.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Vector2D.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Vector3D.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Backend" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Backend/Effekseer.GraphicsDevice.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Network" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Network/Effekseer.Server.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Network" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Network/Effekseer.Client.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Utils" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Utils/Effekseer.CustomAllocator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Utils" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Utils/Effekseer.String.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/IO" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/IO/Effekseer.EfkEfcFactory.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Base.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Float4.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Float4_Gen.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Float4_NEON.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Float4_SSE.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Int4.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Int4_Gen.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Int4_NEON.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Int4_SSE.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Bridge.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Bridge_Gen.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Bridge_NEON.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Bridge_SSE.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Vec2f.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Vec3f.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Vec4f.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Mat43f.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Mat44f.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Quaternionf.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/SIMD" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/SIMD/Utils.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Parameter" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Parameter/Effekseer.Parameters.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Renderer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Renderer/Effekseer.SpriteRenderer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Renderer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Renderer/Effekseer.RibbonRenderer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Renderer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Renderer/Effekseer.RingRenderer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Renderer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Renderer/Effekseer.ModelRenderer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Renderer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Renderer/Effekseer.TrackRenderer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Renderer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Renderer/Effekseer.GpuTimer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Renderer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Renderer/Effekseer.GpuParticles.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.EffectLoader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.TextureLoader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.MaterialLoader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.Curve.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.CurveLoader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.SoundLoader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.WorkerThread.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Effekseer.ResourceManager.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Model" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Model/Effekseer.Model.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Model" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Model/Effekseer.ModelLoader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/Sound" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/Sound/Effekseer.SoundPlayer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/VectorField" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/VectorField/Effekseer.VectorField.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Effekseer/VectorField" TYPE FILE FILES "C:/dev/raylib-effekseer/thirdparty/Effekseer/Effekseer/VectorField/Effekseer.VectorFieldLoader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/Debug/Effekseer.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/Release/Effekseer.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/MinSizeRel/Effekseer.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/RelWithDebInfo/Effekseer.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Effekseer-config.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Effekseer-config.cmake"
         "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/CMakeFiles/Export/c220ae0af1591e9e9e916bba91f25986/Effekseer-config.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Effekseer-config-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Effekseer-config.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/CMakeFiles/Export/c220ae0af1591e9e9e916bba91f25986/Effekseer-config.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/CMakeFiles/Export/c220ae0af1591e9e9e916bba91f25986/Effekseer-config-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/CMakeFiles/Export/c220ae0af1591e9e9e916bba91f25986/Effekseer-config-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/CMakeFiles/Export/c220ae0af1591e9e9e916bba91f25986/Effekseer-config-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/CMakeFiles/Export/c220ae0af1591e9e9e916bba91f25986/Effekseer-config-release.cmake")
  endif()
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/dev/raylib-effekseer/build/thirdparty/Effekseer/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
