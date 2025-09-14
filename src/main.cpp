#include <iostream>
#include <string>

#include <main.h>

#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl3.h>
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

  gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
  SDL_GL_SetSwapInterval(0);
  float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
                           0.5f,  -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
                           0.0f,  0.5f,  0.0f, 0.2f, 0.2f, 0.8f, 1.0f};

  while (!done) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        done = true;
      }
      glClearColor(0.2, 0.2, 0.2, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      SDL_GL_SwapWindow(window);
    }
  }

  SDL_GL_DestroyContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}