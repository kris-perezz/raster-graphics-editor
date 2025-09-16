#pragma once

#include <src/RGE_pch.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>
#include <src/ComputeShader.h>
#include <src/CanvasState.h>

namespace RGE {
class GUI {

public:
  GUI(SDL_Window *window, SDL_GLContext context, float mainScale, const char *glslVersion,
         const std::shared_ptr<RGE::ComputeShader> computeShader, uint32_t texture);
  ~GUI();

  void render(CanvasState &state, uint32_t texture);

  void draw();

private:
  std::shared_ptr<RGE::ComputeShader> m_computeShader;
  uint32_t m_texture;

  ImGuiIO *io;

  ImVec4 clear_color;
  ImVec4 brushColour;
  ImVec4 clearColour;
  bool clear;
  ImVec2 canvasSize;
};
} // namespace RGE