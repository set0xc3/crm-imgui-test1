cmake_minimum_required(VERSION 3.10)

set(NAMESPACE crm)
project(${NAMESPACE}-tests LANGUAGES CXX)

set(TARGET_ARCHITECTURE "x64")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

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

include_directories(
  ../crm/src
  ${CMAKE_SOURCE_DIR}/vendor/cbased/cbased/src
  ${CMAKE_SOURCE_DIR}/vendor/cbased/vendor/glad/include
  ${CMAKE_SOURCE_DIR}/vendor/cbased/vendor/Unity/src
  ${CMAKE_SOURCE_DIR}/vendor/imgui
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends
  ${SDL2_INCLUDE_DIRS}
)

link_libraries(
  ${SDL2_LIBRARIES}
  crm-static
  cbased
  imgui
  unity
)

if (DEFINED ENV{PG_INCLUDE_DIR})
    include_directories($ENV{PG_INCLUDE_DIR})
else()
    include_directories(/usr/include/postgresql)
endif()

file(GLOB_RECURSE TEST_SRC_FILES test_*.cpp)

add_custom_target(${NAMESPACE}-run_tests)

foreach(test_file ${TEST_SRC_FILES})
  get_filename_component(test_name ${test_file} NAME_WE)
  set(generated_file ${NAMESPACE}-${test_name}_gen.cpp)

  add_custom_command(
    OUTPUT ${generated_file}
    COMMAND ${CMAKE_SOURCE_DIR}/vendor/cbased/vendor/Unity/auto/generate_test_runner.rb ${test_file} ${generated_file}
    DEPENDS ${test_file}
  )

  add_executable(${NAMESPACE}-${test_name}.bin ${test_file} ${generated_file})
  add_custom_target(${NAMESPACE}-${test_name} DEPENDS ${generated_file})
  add_dependencies(${NAMESPACE}-${test_name}.bin ${NAMESPACE}-${test_name})

  add_custom_command(
    COMMENT "Running ${NAMESPACE}-${test_name}.bin"
    TARGET ${NAMESPACE}-run_tests POST_BUILD
    DEPENDS ${NAMESPACE}-${test_name}.bin
    COMMAND $<TARGET_FILE:${NAMESPACE}-${test_name}.bin>
  )

  add_custom_target(${NAMESPACE}-run_${test_name}
    COMMENT "Running ${NAMESPACE}-${test_name}.bin"
    DEPENDS ${NAMESPACE}-${test_name}.bin
    COMMAND $<TARGET_FILE:${NAMESPACE}-${test_name}.bin>
  )

  # add_custom_command(
  #   COMMENT "Running ${NAMESPACE}-${test_name}.bin"
  #   TARGET ${NAMESPACE}-${test_name}.bin POST_BUILD
  #   COMMAND $<TARGET_FILE:${NAMESPACE}-${test_name}.bin>
  # )

  # add_custom_target(${NAMESPACE}-run_${test_name} ALL
  #   COMMENT "Running ${NAMESPACE}-${test_name}.bin"
  #   DEPENDS ${NAMESPACE}-${test_name}.bin
  #   COMMAND $<TARGET_FILE:${NAMESPACE}-${test_name}.bin>
  # )
endforeach()

add_dependencies(run_tests ${NAMESPACE}-run_tests)
