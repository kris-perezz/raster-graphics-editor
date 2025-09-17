cmake_minimum_required(VERSION 3.10)

project(RGE VERSION 1.0)

include(FetchContent)

cmake_policy(SET CMP0072 NEW)

set(RGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


option(SDL_VENDORED OFF)

if(SDL_VENDORED)
  
  FetchContent_Declare(
      SDL3
      GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
      GIT_TAG origin/main
      OVERRIDE_FIND_PACKAGE
  )
  set(SDL_SHARED OFF)
  set(SDL_STATIC ON)
  FetchContent_MakeAvailable(SDL3)

else()
  find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)

set(RGE_HEADER 
    src/main.h
    src/Shader.h
    src/ComputeShader.h
    src/Application.h
    src/GUI.h
    src/Renderer.h
    src/CanvasState.h)


set(RGE_SOURCE
    src/Shader.cpp
    src/ComputeShader.cpp
    src/Application.cpp
    src/GUI.cpp
    src/Renderer.cpp)

add_subdirectory(include/glad)
add_subdirectory(include/imgui)

add_library(RGE_Engine ${RGE_SOURCE} ${RGE_HEADER})

target_precompile_headers(RGE_Engine PRIVATE src/RGE_pch.h)

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
add_executable(DEMO src/imgui_demo.cpp)

target_link_libraries(RGE PRIVATE RGE_Engine)
target_link_libraries(DEMO PRIVATE RGE_Engine)

if(WIN32)
  foreach(exe RGE DEMO)
    # Copy SDL3.dll beside the exe
    add_custom_command(TARGET ${exe} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL3::SDL3>"
        $<TARGET_FILE_DIR:${exe}>)

    # Copy data folder beside the exe
    add_custom_command(TARGET ${exe} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:${exe}>/data")
  endforeach()
else()
  # Linux
  set(RUN_DATA_DIR ${CMAKE_BINARY_DIR}/data)
  execute_process(COMMAND ${CMAKE_COMMAND} -E rm -rf "${RUN_DATA_DIR}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                          "${CMAKE_SOURCE_DIR}/data" "${RUN_DATA_DIR}")
  target_include_directories(RGE_Engine PUBLIC "${RUN_DATA_DIR}")
endif()

install(TARGETS RGE DEMO RGE_Engine
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

if(WIN32)
  install(FILES "$<TARGET_FILE:SDL3::SDL3>" DESTINATION bin)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION share/RGE)

include(CPack)