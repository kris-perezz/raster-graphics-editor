#pragma once

#include <src/RAGE_pch.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_internal.h>
#include <src/CanvasState.h>

namespace RAGE {
class GUI {

public:
  bool quitRequest = false;
  bool quitConfirmed = false;

  GUI(SDL_Window *window, SDL_GLContext context, float mainScale, const char *glslVersion,
      uint32_t texture);
  ~GUI();

  void render(CanvasState &state, uint32_t texture);

  void draw();

private:
  uint32_t m_texture;

  ImGuiIO *io;

  ImGuiViewport *m_viewport;
};
} // namespace RAGE