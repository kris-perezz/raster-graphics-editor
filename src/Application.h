#pragma once

#include <src/RGE_pch.h>
#include <src/GUI.h>
#include <src/ComputeShader.h>

namespace RGE {
  class Application {
    public:
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

  };
}