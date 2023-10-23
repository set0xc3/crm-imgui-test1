cmake_minimum_required(VERSION 3.10)

set(TARGET crm-tests)
project(${TARGET} LANGUAGES CXX)

set(TARGET_ARCHITECTURE "x64")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/crm/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/crm/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/crm/bin)

set(CMAKE_CXX_STANDARD 11)

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

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(
  ../crm/src
  ${CMAKE_SOURCE_DIR}/vendor/cbased/cbased/src
  ${CMAKE_SOURCE_DIR}/vendor/cbased/vendor/glad/include
  ${CMAKE_SOURCE_DIR}/vendor/imgui
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends
  ${SDL2_INCLUDE_DIRS}
)

link_libraries(
  ${SDL2_LIBRARIES}
  crm-static
  cbased
  imgui
)

if (DEFINED ENV{PG_INCLUDE_DIR})
    include_directories($ENV{PG_INCLUDE_DIR})
else()
    include_directories(/usr/include/postgresql)
endif()

add_executable(test_db.bin test_db.cpp)
add_executable(test_imgui.bin test_imgui.cpp)
add_custom_target(crm-test_db ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_db.bin)
add_custom_target(crm-test_imgui ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_imgui.bin)

# file(GLOB_RECURSE TESTS_SRC_FILES *.cpp)
# foreach(test_file ${TESTS_SRC_FILES})
#   get_filename_component(test_name ${test_file} NAME_WE)
#   add_executable(${test_name}.bin ${test_file})
# endforeach()
#
# file(GLOB BINARIES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/*.bin")
# set(TEST_TARGETS "")
#
# foreach(BINARY ${BINARIES})
#   get_filename_component(BINARY_NAME ${BINARY} NAME_WE)
#   add_custom_command(OUTPUT ${BINARY_NAME}.out
#                      COMMAND ${BINARY}
#                      DEPENDS ${BINARY}
#                      COMMENT "Running ${BINARY}"
#                      VERBATIM)
#   add_custom_target(crm-${BINARY_NAME} DEPENDS ${BINARY_NAME}.out)
#   list(APPEND TEST_TARGETS ${BINARY_NAME})
# endforeach()
#
# add_custom_target(crm-tests DEPENDS ${TEST_TARGETS})
#
