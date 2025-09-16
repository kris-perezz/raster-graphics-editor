#pragma once

#include <src/RGE_pch.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>
#include <src/ComputeShader.h>

namespace RGE {
class GUI {

public:
  GUI(SDL_Window *window, SDL_GLContext *context, float mainScale, const char *glslVersion,
      const std::shared_ptr<RGE::ComputeShader> m_computeShader, uint32_t m_texture);
  ~GUI();

  void render();
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