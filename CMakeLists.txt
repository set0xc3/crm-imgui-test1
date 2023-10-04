cmake_minimum_required(VERSION 3.10)

add_subdirectory(vendor/cbased)

set(TARGET crm)
project(${TARGET} LANGUAGES CXX)

set(TARGET_ARCHITECTURE "x64")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

set(IMGUI_SRC_FILES 
  vendor/imgui/imgui.cpp
  vendor/imgui/imgui_demo.cpp
  vendor/imgui/imgui_draw.cpp
  vendor/imgui/imgui_tables.cpp
  vendor/imgui/imgui_widgets.cpp
  vendor/imgui/backends/imgui_impl_sdl2.cpp
  vendor/imgui/backends/imgui_impl_opengl2.cpp
)

add_executable(${TARGET} ${SRC_FILES} ${IMGUI_SRC_FILES})

target_compile_options(${TARGET} PRIVATE 
  -g 
  -O0
  -Wall 
  -Wextra 
  -Wno-gnu-zero-variadic-macro-arguments 
  -Wno-unused-parameter 
  -Wno-unused-variable 
  -Wno-unused-but-set-variable 
  -Wno-macro-redefined 
  -Wno-attributes 
  -Wno-incompatible-library-redeclaration
)

find_package(SDL2 REQUIRED)

target_include_directories(${TARGET} PRIVATE 
  src 
  vendor/cbased/cbased/src
  vendor/imgui
  vendor/imgui/backends
  ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(${TARGET} PRIVATE
  cbased
)
