#pragma once

#include <src/ComputeShader.h>
#include <src/GUI.h>
#include <src/RGE_pch.h>
#include <src/Renderer.h>
#include <src/Shader.h>

namespace RGE {
class Application {
public:
  CanvasState state{};
  Application(const std::string &application);
  virtual ~Application();

  void run();
  void getName();

private:
  SDL_Window *m_window;
  SDL_GLContext m_context;
  const char *m_glslVersion;
  float m_mainScale;

  std::unique_ptr<RGE::GUI> m_GUI;
  std::shared_ptr<RGE::ComputeShader> m_computeShader;
  std::shared_ptr<RGE::Shader> m_shader;
  std::unique_ptr<RGE::Renderer> m_renderer;

  uint32_t m_texture = 0;
};
} // namespace RGE