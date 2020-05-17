#### DO not run against CMake directly!
#### Meant to be used with gdnative-project as a "subproject"
#### https://github.com/hlfstr/gdnative-project

cmake_minimum_required(VERSION 3.15)
# Set name of project to current directory name
get_filename_component(LibName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" LibName ${LibName})
project(${LibName} LANGUAGES CXX)

# Set output directory
set(OUTPATH "${PROJECT_BINARY_DIR}/lib/${SYSTEM_NAME}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPATH}")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Find all source files in source dir
file(GLOB_RECURSE LIBSOURCES ${PROJECT_SOURCE_DIR}/*.c**)
file(GLOB_RECURSE LIBHEADERS ${PROJECT_SOURCE_DIR}/*.h**)

# Define library
add_library(${LibName} STATIC ${LIBSOURCES} ${LIBHEADERS})
add_dependencies(${LibName} libgodot-cpp)

# Set target features
target_compile_features(${LibName} PUBLIC cxx_std_17)
set_target_properties(${LibName} PROPERTIES PREFIX "lib")
if(ANDROID)
	set_target_properties(${LibName} PROPERTIES OUTPUT_NAME "${LibName}.${ANDROID_ABI}")
else()
  set_target_properties(${LibName} PROPERTIES OUTPUT_NAME "${LibName}.${BITS}")
endif()

# Include godot-cpp and other needed stuff
target_include_directories(${LibName}
  PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${SourceDir}/include/godot-cpp/include
  ${SourceDir}/include/godot-cpp/include/core
  ${SourceDir}/include/godot-cpp/include/gen
  ${PROJECT_BINARY_DIR}/gen
)

# Include godot_headers and ignore any warnings
target_include_directories(${LibName}
  SYSTEM PUBLIC ${SourceDir}/include/godot-cpp/godot_headers
)

# Set compile flags
set_property(TARGET ${LibName} APPEND_STRING PROPERTY COMPILE_FLAGS ${C_FLAGS})
set_property(TARGET ${LibName} APPEND_STRING PROPERTY LINK_FLAGS ${L_FLAGS})

# Include libgodot-cpp
target_link_libraries(${LibName} godot-cpp)

# Add this to the main target
target_include_directories(${ProjectId}
  PUBLIC
  ${PROJECT_SOURCE_DIR}
)

# Add this as a dependency of the main project
add_dependencies(${ProjectId} ${LibName})
target_link_libraries(${ProjectId} ${LibName})