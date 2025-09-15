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

  // GL 4.3 + GLSL 130
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

  float vertices[] = {
      0.5f,  0.5f,  0.0f, 0.8f, 0.2f, 0.2f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f  // top left
  };
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  unsigned int EBO;
  glGenBuffers(1, &EBO);

  // 1. bind Vertex Array Object
  glBindVertexArray(VAO);
  // 2. copy our vertices array in a vertex buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // 3. copy our index array in a element buffer for OpenGL to use
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  // 4. then set the vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  const char *base = SDL_GetBasePath();
  std::string vPath = std::string(base) + "data/basic.vert";
  std::string fPath = std::string(base) + "data/basic.frag";

  auto shader = std::make_shared<Shader>(vPath.c_str(), fPath.c_str());

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
      ImGui::Begin("Canvas");

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
      ImGui::Text("Mouse clicked count:");
      for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
        if (io.MouseClickedCount[i] > 0) {
          ImGui::SameLine();
          ImGui::Text("b%d: %d", i, io.MouseClickedCount[i]);
        }

      // We iterate both legacy native range and named ImGuiKey ranges. This is
      // a little unusual/odd but this allows displaying the data for old/new
      // backends. User code should never have to go through such hoops! You can
      // generally iterate between ImGuiKey_NamedKey_BEGIN and
      // ImGuiKey_NamedKey_END.
      struct funcs {
        static bool IsLegacyNativeDupe(ImGuiKey) { return false; }
      };
      ImGuiKey start_key = ImGuiKey_NamedKey_BEGIN;
      ImGui::Text("Keys down:");
      for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
        if (funcs::IsLegacyNativeDupe(key) || !ImGui::IsKeyDown(key))
          continue;
        ImGui::SameLine();
        ImGui::Text((key < ImGuiKey_NamedKey_BEGIN) ? "\"%s\"" : "\"%s\" %d",
                    ImGui::GetKeyName(key), key);
      }
      ImGui::Text("Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "",
                  io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");

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

      ImGui::Text("This is some useful text.");

      ImGui::ColorEdit3("clear color",
                        (float *)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button")) {
        counter++;
      }
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
                  io.Framerate);

      static ImVec4 color =
          ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
      static ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;

      ImGui::ColorEdit3("MyColor##1", (float *)&color, base_flags);
      ImGui::ColorEdit4("MyColor##3", (float *)&color, ImGuiColorEditFlags_DisplayRGB | base_flags);
      ImGui::ColorPicker4("##picker", (float *)&color, base_flags | ImGuiColorEditFlags_DisplayRGB);
      ImGui::End();
    }

    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

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

  shader.reset();
  SDL_GL_DestroyContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}