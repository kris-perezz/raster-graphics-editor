#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <main.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>

#include <src/Application.h>

int main(int, char **) {
  auto app = std::make_unique<RGE::Application>("raster-graphics-editor");

  app->run();
  
  return 0;
}