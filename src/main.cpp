#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <main.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>

int main(int, char **) {

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    printf("Error: SDL_Init(): %s\n", SDL_GetError());
    return -1;
  }

  // GL 4.3 + GLSL 430
  const char *glsl_version = "#version 430";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
  SDL_WindowFlags window_flags =
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
  SDL_Window *window = SDL_CreateWindow("Dear ImGui SDL3+OpenGL3 example", (int)(1280 * main_scale),
                                        (int)(720 * main_scale), window_flags);
  if (window == nullptr) {
    printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
    return -1;
  }
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  if (gl_context == nullptr) {
    printf("Error: SDL_GL_CreateContext(): %s\n", SDL_GetError());
    return -1;
  }

  SDL_GL_MakeCurrent(window, gl_context);

  SDL_GL_SetSwapInterval(0); // Enable vsync
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  SDL_ShowWindow(window);

  if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
    std::fprintf(stderr, "gladLoadGLLoader failed\n");
    return -1;
  }
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup scaling
  ImGuiStyle &style = ImGui::GetStyle();
  style.ScaleAllSizes(main_scale);
  style.FontScaleDpi = main_scale;
  io.ConfigDpiScaleFonts = true;
  io.ConfigDpiScaleViewports = true;

  // Setup Platform/Renderer backends
  ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);

  const char *base = SDL_GetBasePath();
  std::string cPath = std::string(base) + "data/compute.glsl";

  auto computeShader = std::make_shared<ComputeShader>(cPath.c_str());

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  ImVec4 brushColour = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  ImVec4 clearColour = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  bool clear = true;

  unsigned int texture;
  const ImVec2 canvasSize(512, 512);

  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, canvasSize.x, canvasSize.y, 0, GL_RGBA, GL_FLOAT,
               nullptr);
  // Main loop
  bool done = false;
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);
      if (event.type == SDL_EVENT_QUIT)
        done = true;
      if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
          event.window.windowID == SDL_GetWindowID(window))
        done = true;
    }

    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
      SDL_Delay(10);
      continue;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    {
      ImGui::Begin("Debug");
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
                  io.Framerate);

      if (ImGui::IsMousePosValid())
        ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
      else
        ImGui::Text("Mouse pos: <INVALID>");
      ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
      ImGui::Text("Mouse down:");
      for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
        if (ImGui::IsMouseDown(i)) {
          ImGui::SameLine();
          ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]);
        }
      ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);
      ImGui::Text("io.WantCaptureMouse: %d", io.WantCaptureMouse);
      ImGui::Text("io.WantCaptureMouseUnlessPopupClose: %d", io.WantCaptureMouseUnlessPopupClose);
      ImGui::Text("io.WantCaptureKeyboard: %d", io.WantCaptureKeyboard);
      ImGui::Text("io.WantTextInput: %d", io.WantTextInput);
      ImGui::Text("io.WantSetMousePos: %d", io.WantSetMousePos);
      ImGui::Text("io.NavActive: %d, io.NavVisible: %d", io.NavActive, io.NavVisible);
      ImGui::End();
    }
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Raster Graphics Editor"); // Create a window called Raster
      // Graphics Editor

      ImGui::ColorEdit3("clear color",
                        (float *)&clear_color); // Edit 3 floats representing a color

      static ImVec4 color =
          ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
      static ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;

      ImGui::ColorEdit3("Canvas Clear  Colour", (float *)&clearColour);

      ImGui::ColorPicker4("##picker", (float *)&brushColour,
                          base_flags | ImGuiColorEditFlags_DisplayRGB);

      if (ImGui::Button("Clear Canvas", ImVec2(200, 60))) {
        clear = true;
      }
      ImGui::End();
    }
    {
      ImGui::SetNextWindowSize(canvasSize, ImGuiCond_Once);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

      ImGui::Begin("Canvas", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar |
                       ImGuiWindowFlags_NoMove);

      ImVec2 mousePosition;
      if (io.WantCaptureMouse) {
        mousePosition.x = ImGui::GetMousePos().x - ImGui::GetWindowPos().x;
        mousePosition.y = ImGui::GetMousePos().y - ImGui::GetWindowPos().y;
      }

      computeShader->bind();
      glUniform2f(0, mousePosition.x, mousePosition.y);
      glUniform4f(1, brushColour.x, brushColour.y, brushColour.z, brushColour.w);
      glUniform1i(2, clear ? 1 : 0);
      glUniform4f(3, clearColour.x, clearColour.y, clearColour.z, clearColour.w);

      if (clear || ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        computeShader->bind();

        glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

        glDispatchCompute(canvasSize.x, canvasSize.y, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
        clear = false;
      }

      ImGui::Image((void *)(intptr_t)texture, canvasSize);
      ImGui::End();
      ImGui::PopStyleVar();
    }
    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      SDL_Window *backup_current_window = SDL_GL_GetCurrentWindow();
      SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }

    SDL_GL_SwapWindow(window);
  }

  // Cleanup

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  computeShader.reset();
  SDL_GL_DestroyContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}