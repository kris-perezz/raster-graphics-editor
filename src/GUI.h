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

  GUI(SDL_Window *window, SDL_GLContext context, float mainScale, const char *glslVersion, uint32_t texture);
  ~GUI();

  void render(CanvasState &state, uint32_t texture);

  void draw();
  const ImVec2 &lastCanvasScreenPos() const { return m_lastCanvasPos; }
  const ImVec2 &lastCanvasScreenSize() const { return m_lastCanvasSize; }

private:
  ImVec2 m_lastCanvasPos;
  ImVec2 m_lastCanvasSize;
  uint32_t m_texture;

  ImGuiIO *io;

  ImGuiViewport *m_viewport;
};
} // namespace RAGE