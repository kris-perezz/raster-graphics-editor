#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>
#include <src/RAGE_pch.h>

namespace RAGE {
struct CanvasState {
  ImVec4 viewportColour = ImVec4(0.2f, 0.3f, 0.4f, 1.0f);
  ImVec4 canvasColour = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
  ImVec4 brushColour = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  bool clear = false;
  ImVec2 mousePosition = ImVec2(-1, -1);
  bool draw = false;
  ImVec2 canvasSize = ImVec2(512, 512);
  bool save = false;
  std::string pendingSavePath;
};
} // namespace RAGE