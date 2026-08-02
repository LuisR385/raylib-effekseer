cmake_minimum_required(VERSION 3.20)

project(raylib_effekseer
  VERSION 0.1.0
  LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------
# raylib
# -----------------------------------------------------------------------------

set(RAYLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib" CACHE PATH "Path to the bundled raylib package")
set(RAYLIB_INCLUDE_DIR "${RAYLIB_ROOT}/include")
set(RAYLIB_LIBRARY_DIR "${RAYLIB_ROOT}/lib")

if(WIN32)
  set(RAYLIB_DLL "${RAYLIB_LIBRARY_DIR}/raylib.dll")
  set(RAYLIB_IMPORT_LIBRARY "${RAYLIB_LIBRARY_DIR}/raylibdll.lib")

  if(NOT EXISTS "${RAYLIB_IMPORT_LIBRARY}")
    set(RAYLIB_IMPORT_LIBRARY "${RAYLIB_LIBRARY_DIR}/raylib.lib")
  endif()

  if(NOT EXISTS "${RAYLIB_IMPORT_LIBRARY}")
    message(FATAL_ERROR "raylib import library was not found in ${RAYLIB_LIBRARY_DIR}")
  endif()

  add_library(raylib::raylib SHARED IMPORTED GLOBAL)
  set_target_properties(raylib::raylib PROPERTIES
    IMPORTED_IMPLIB "${RAYLIB_IMPORT_LIBRARY}"
    IMPORTED_LOCATION "${RAYLIB_DLL}"
    INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_INCLUDE_DIR}"
  )
else()
  find_package(raylib CONFIG REQUIRED)
endif()

# -----------------------------------------------------------------------------
# Effekseer
# -----------------------------------------------------------------------------
# Use either installed package targets or the bundled Effekseer 1.80.6 sources.

# These helpers normally come from Effekseer's top-level CMake project.  This
# project embeds only the runtime subdirectories, so provide the small amount of
# glue their CMakeLists expect.
if(NOT COMMAND filterfolder)
  function(filterfolder sources)
    foreach(source IN LISTS sources)
      get_filename_component(group "${source}" DIRECTORY)
      string(REPLACE "/" "\\" group "${group}")
      source_group("${group}" FILES "${source}")
    endforeach()
  endfunction()
endif()

if(NOT COMMAND warnerror)
  function(warnerror target)
    if(MSVC)
      target_compile_options(${target} PRIVATE /we4267 /we4456 /we4458 /we4715)
    endif()
  endfunction()
endif()

find_package(Effekseer CONFIG QUIET)
find_package(EffekseerRendererGL CONFIG QUIET)

if(NOT TARGET Effekseer AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/Effekseer/CMakeLists.txt")
  add_subdirectory(thirdparty/Effekseer)
endif()

if(NOT TARGET EffekseerRendererCommon
   AND TARGET Effekseer
   AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/EffekseerRendererCommon/CMakeLists.txt")
  add_subdirectory(thirdparty/EffekseerRendererCommon)
endif()

if(NOT TARGET EffekseerRendererGL
   AND TARGET Effekseer
   AND TARGET EffekseerRendererCommon
   AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/EffekseerRendererGL/CMakeLists.txt")
  add_subdirectory(thirdparty/EffekseerRendererGL)
endif()

# -----------------------------------------------------------------------------
# Bridge target
# -----------------------------------------------------------------------------

add_library(raylib_effekseer INTERFACE)
add_library(raylib_effekseer::raylib_effekseer ALIAS raylib_effekseer)

target_sources(raylib_effekseer
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/rayseer.h"
)

target_include_directories(raylib_effekseer
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(raylib_effekseer
  INTERFACE
    raylib::raylib
)

if(TARGET Effekseer)
  target_link_libraries(raylib_effekseer
    INTERFACE
      Effekseer
  )
endif()

if(TARGET EffekseerRendererGL)
  target_link_libraries(raylib_effekseer
    INTERFACE
      EffekseerRendererGL
  )
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
  add_executable(raylib_effekseer_example
    src/main.cpp
  )

  target_link_libraries(raylib_effekseer_example
    PRIVATE
      raylib_effekseer::raylib_effekseer
  )
endif()

# Copy the raylib DLL next to executables that link this bridge target.
if(WIN32 AND EXISTS "${RAYLIB_DLL}")
  add_custom_target(copy_raylib_dll ALL
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${RAYLIB_DLL}"
            "${CMAKE_BINARY_DIR}/raylib.dll"
    COMMENT "Copying raylib.dll to the build directory"
  )
  add_dependencies(raylib_effekseer copy_raylib_dll)

  if(TARGET raylib_effekseer_example)
    add_dependencies(raylib_effekseer_example copy_raylib_dll)
  endif()
endif()
