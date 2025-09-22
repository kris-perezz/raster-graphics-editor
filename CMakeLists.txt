cmake_minimum_required(VERSION 3.10)

project(RAGE VERSION 1.0)

include(FetchContent)

cmake_policy(SET CMP0072 NEW)

set(RAGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



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

set(RAGE_HEADER 
    src/main.h
    src/Shader.h
    src/ComputeShader.h
    src/Application.h
    src/GUI.h
    src/Renderer.h
    src/CanvasState.h)


set(RAGE_SOURCE
    src/Shader.cpp
    src/ComputeShader.cpp
    src/Application.cpp
    src/GUI.cpp
    src/Renderer.cpp)

add_subdirectory(include/glad)
add_subdirectory(include/imgui)
add_subdirectory(include/stb)
add_subdirectory(include/ImGuiFileDialog)
add_subdirectory(include/dirent)

add_library(RAGE_Engine ${RAGE_SOURCE} ${RAGE_HEADER})

target_precompile_headers(RAGE_Engine PRIVATE src/RAGE_pch.h)

target_include_directories(
  RAGE_Engine 
  PUBLIC ${RAGE_ROOT_PATH}
  PUBLIC ${RAGE_ROOT_PATH}/src
  PUBLIC ${RAGE_ROOT_PATH}/include
  PUBLIC ${RAGE_ROOT_PATH}/include/imgui)

target_link_libraries(
  RAGE_Engine 
  glad
  glm
  imgui
  ImGuiFileDialog
  stb
  dirent
  SDL3::SDL3
  ${OPENGL_LIBRARIES})

add_executable(RAGE src/main.cpp)
add_executable(DEMO src/imgui_demo.cpp)

target_link_libraries(RAGE PRIVATE RAGE_Engine)
target_link_libraries(DEMO PRIVATE RAGE_Engine)

if(WIN32)
  foreach(exe RAGE DEMO)
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
  target_include_directories(RAGE_Engine PUBLIC "${RUN_DATA_DIR}")
endif()

# Binaries/libs
install(TARGETS RAGE DEMO RAGE_Engine
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

# SDL runtime on Windows
if(WIN32)
  install(FILES "$<TARGET_FILE:SDL3::SDL3>" DESTINATION bin)
endif()

# Assets next to the exe (required by SDL_GetBasePath() + "data/..."):
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION bin)

# CPack config
set(CPACK_PACKAGE_NAME "RAGE")
set(CPACK_PACKAGE_VENDOR "RAGE")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Raster Graphics Editor")
set(CPACK_RESOURCE_FILE_README  "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

# Generators
# build a zip for all, NSIS installer on Windows if NSIS is installed
if(WIN32)
  set(CPACK_GENERATOR "ZIP;NSIS")
  set(CPACK_NSIS_DISPLAY_NAME "RAGE")
  set(CPACK_NSIS_PACKAGE_NAME "RAGE")
  set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "RAGE")
else()
  set(CPACK_GENERATOR "TGZ;TXZ;ZIP")
endif()

# Nice file name: RAGE-1.0.0-windows-x86_64.zip, etc.
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)