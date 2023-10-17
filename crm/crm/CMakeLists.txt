cmake_minimum_required(VERSION 3.10)

set(TARGET crm)
project(${TARGET} LANGUAGES CXX)

set(TARGET_ARCHITECTURE "x64")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

if (DEFINED ENV{PG_INCLUDE_DIR})
    include_directories($ENV{PG_INCLUDE_DIR})
else()
    include_directories(/usr/include/postgresql)
endif()

link_libraries(cbased glad imgui)

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

find_package(SDL2 REQUIRED)

include_directories( 
  src
  ${CMAKE_SOURCE_DIR}/vendor/cbased/cbased/src
  ${CMAKE_SOURCE_DIR}/vendor/glad/include
  ${CMAKE_SOURCE_DIR}/vendor/imgui
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends
  ${SDL2_INCLUDE_DIRS}
)

add_executable(${TARGET} ${SRC_FILES})
add_library(${TARGET}-static STATIC ${SRC_FILES})

add_custom_target(run-${TARGET} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/crm)

# Asset files
set(ASSETS_SRC "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_DST "$<TARGET_FILE_DIR:${TARGET}>/assets")

if(WIN32)
    set(ASSETS_CMD copy_directory)
    set(ASSETS_MSG "Copy assets")
else()
    set(ASSETS_CMD create_symlink)
    set(ASSETS_MSG "Link assets")
endif()

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "${ASSETS_MSG}: ${ASSETS_SRC} to ${ASSETS_DST}"
    COMMAND ${CMAKE_COMMAND} -E ${ASSETS_CMD} "${ASSETS_SRC}" "${ASSETS_DST}"
)
