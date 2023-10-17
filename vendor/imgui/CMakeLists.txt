cmake_minimum_required(VERSION 3.10)

set(TARGET imgui)
project(${TARGET} LANGUAGES CXX)

set(TARGET_ARCHITECTURE "x64")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(IMGUI_SRC_FILES 
  imgui.cpp
  imgui_demo.cpp
  imgui_draw.cpp
  imgui_tables.cpp
  imgui_widgets.cpp
  backends/imgui_impl_sdl2.cpp
  backends/imgui_impl_opengl3.cpp
)

find_package(SDL2 REQUIRED)

add_compile_options(
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

add_library(${TARGET} ${IMGUI_SRC_FILES})

target_include_directories(${TARGET} PRIVATE
  .
  ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(${TARGET} PRIVATE 
  GL 
  ${SDL2_LIBRARIES}
)
