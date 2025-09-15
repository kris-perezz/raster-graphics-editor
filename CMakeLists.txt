cmake_minimum_required(VERSION 3.10)

project(RGE
        VERSION 1.0)

include(FetchContent)
cmake_policy(SET CMP0072 NEW)

set(RGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


option(SDL_VENDORED OFF)

if(SDL_VENDORED)
  set(SDL_SHARED OFF)
  set(SDL_STATIC ON)
  FetchContent_Declare(
      SDL3
      GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
      GIT_TAG origin/main
      OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(SDL3)

else()
  find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

set(RGE_HEADER 
    src/main.h)

# Set our source files
set(RGE_SOURCE)



add_subdirectory(include/glad)
add_subdirectory(include/imgui)
# Add our library
add_library(RGE_Engine ${RGE_SOURCE} ${RGE_HEADER})

target_include_directories(
  RGE_Engine 
  PUBLIC ${RGE_ROOT_PATH}
  PUBLIC ${RGE_ROOT_PATH}/src
  PUBLIC ${RGE_ROOT_PATH}/include
  PUBLIC ${RGE_ROOT_PATH}/include/imgui)

target_link_libraries(
  RGE_Engine 
  glad
  glm
  imgui
  SDL3::SDL3
  ${OPENGL_LIBRARIES})

add_executable(RGE src/main.cpp)

target_link_libraries(RGE PRIVATE RGE_Engine)

set(RUN_DATA_DIR ${CMAKE_BINARY_DIR}/data)
file(MAKE_DIRECTORY "${RUN_DATA_DIR}")

execute_process(COMMAND ${CMAKE_COMMAND} -E rm -rf "${RUN_DATA_DIR}")
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                        "${CMAKE_SOURCE_DIR}/data" "${RUN_DATA_DIR}")

target_include_directories(RGE_Engine PUBLIC "${RUN_DATA_DIR}")
