project(ImGuiFileDialog)

add_library(ImGuiFileDialog STATIC
    ImGuiFileDialog.cpp
    ImGuiFileDialog.h
    ImGuiFileDialogConfig.h
)

target_include_directories(ImGuiFileDialog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ImGuiFileDialog PUBLIC ${RAGE_ROOT_PATH}/include)


target_link_libraries(ImGuiFileDialog PUBLIC imgui dirent)
