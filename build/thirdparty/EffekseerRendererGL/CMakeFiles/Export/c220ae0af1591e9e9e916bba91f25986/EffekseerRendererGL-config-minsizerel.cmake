#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "EffekseerRendererGL" for configuration "MinSizeRel"
set_property(TARGET EffekseerRendererGL APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(EffekseerRendererGL PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/EffekseerRendererGL.lib"
  )

list(APPEND _cmake_import_check_targets EffekseerRendererGL )
list(APPEND _cmake_import_check_files_for_EffekseerRendererGL "${_IMPORT_PREFIX}/lib/EffekseerRendererGL.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
