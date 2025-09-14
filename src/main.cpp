#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <iostream>
#include <string>

#include <main.h>

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui.h>

#include <SDL3/SDL.h>
#include <glad/gl.h>

int main(int argc, char *argv[]) {
  std::cout << "RGE Paint starting up!" << std::endl;

  bool done = false;

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    return 1;
  }

  constexpr SDL_WindowFlags flags =
      SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS |
      SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_RESIZABLE;

  const std::string title = "RGE";
  uint32_t height = 720;
  uint32_t width = 1280;

  bool vsync = false;
  bool fullscreen = false;

  SDL_Window *window = SDL_CreateWindow(title.c_str(), width, height, flags);
  // SDL_Window *window = SDL_CreateWindow("RGE", 1280, 720,
  // SDL_WINDOW_RESIZABLE);
  if (!window) {
    std::cout << "Busted" << std::endl;
    return -1;
  }
  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (context == nullptr) {
    std::cout << "Busted context" << std::endl;
    return -1;
  }
  SDL_GL_MakeCurrent(window, context);
  SDL_GL_SetSwapInterval(0);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

  float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
  ImGui::StyleColorsDark();
  ImGuiStyle& style = ImGui::GetStyle();
  style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
  style.FontScaleDpi = main_scale;   

  const char* glsl_version = "#version 130";
  bool show_demo_window = true;

  // Setup Platform/Renderer backends
  ImGui_ImplSDL3_InitForOpenGL(window, context);
  ImGui_ImplOpenGL3_Init(glsl_version);

  gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
  SDL_GL_SetSwapInterval(0);
  float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
                           0.5f,  -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
                           0.0f,  0.5f,  0.0f, 0.2f, 0.2f, 0.8f, 1.0f};

  while (!done) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      ImGui_ImplSDL3_ProcessEvent(&e);
      if (e.type == SDL_EVENT_QUIT) {
        done = true;
      }
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplSDL3_NewFrame();
      ImGui::NewFrame();

      ImGui::ShowDemoWindow(&show_demo_window);
      ImGui::Render();
      glClearColor(0.2, 0.2, 0.2, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      SDL_GL_SwapWindow(window);
    }
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DestroyContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}