#include <src/Application.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>

namespace RAGE {
Application::Application(const std::string &Application) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(std::string("Error: SDL_Init(): ") + SDL_GetError());
  }

  // GL 4.3 + GLSL 430
  m_glslVersion = "#version 430";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  // Create m_window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  m_mainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

  SDL_WindowFlags window_flags =
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;

  m_window = SDL_CreateWindow(Application.c_str(), (int)(1280 * m_mainScale),
                              (int)(720 * m_mainScale), window_flags);

  if (m_window == nullptr) {
    throw std::runtime_error(std::string("Error: SDL_CreateWindow(): ") + SDL_GetError());
  }
  m_context = SDL_GL_CreateContext(m_window);
  if (m_context == nullptr) {
    throw std::runtime_error(std::string("Error: SDL_GL_CreateContext(): ") + SDL_GetError());
  }

  SDL_GL_MakeCurrent(m_window, m_context);

  SDL_GL_SetSwapInterval(0); // Disable vsync
  SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  SDL_ShowWindow(m_window);

  if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
    std::fprintf(stderr, "gladLoadGLLoader failed\n");
    throw std::runtime_error(std::string("Error: gladLoadGLLoader failed "));
  }

  const char *base = SDL_GetBasePath();
  std::string vPath = std::string(base) + "data/basic.vert";
  std::string fPath = std::string(base) + "data/basic.frag";
  m_shader = std::make_shared<Shader>(vPath.c_str(), fPath.c_str());

  state.canvasSize = {512, 512};
  m_renderer = std::make_unique<Renderer>(m_window, m_shader, m_texture, state);
  m_GUI =
      std::make_unique<GUI>(m_window, m_context, m_mainScale, m_glslVersion, m_renderer->texture());
}

Application::~Application() {
  m_GUI.reset();
  m_computeShader.reset();
  SDL_GL_DestroyContext(m_context);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Application::run() {
  bool done = false;
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);
      if (event.type == SDL_EVENT_QUIT)
        done = true;
      if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
          event.window.windowID == SDL_GetWindowID(m_window))
        done = true;
    }

    if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED) {
      SDL_Delay(10);
      continue;
    }

    m_GUI->render(state, m_renderer->texture());
    m_renderer->setClearColour(state);
    m_renderer->clear();
    m_renderer->clearCanvas(state);
    m_renderer->renderCanvas(state);
    m_renderer->saveImage(state);
    m_GUI->draw();

    SDL_GL_SwapWindow(m_window);
  }
}
} // namespace RAGE