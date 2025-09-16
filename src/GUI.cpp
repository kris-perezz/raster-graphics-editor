#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>
#include <src/GUI.h>

namespace RGE {
GUI::GUI(SDL_Window *window, SDL_GLContext *context, float mainScale, const char *glslVersion,
         const std::shared_ptr<RGE::ComputeShader> computeShader, uint32_t texture)
    : m_computeShader(computeShader), m_texture(texture) {

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = &ImGui::GetIO();

  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  ImGuiStyle &style = ImGui::GetStyle();
  style.ScaleAllSizes(mainScale);
  style.FontScaleDpi = mainScale;
  io->ConfigDpiScaleFonts = true;
  io->ConfigDpiScaleViewports = true;

  // Setup Platform/Renderer backends
  ImGui_ImplSDL3_InitForOpenGL(window, context);
  ImGui_ImplOpenGL3_Init(glslVersion);

   clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
   brushColour = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
   clearColour = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
   clear = true;

  canvasSize.x = 512;
  canvasSize.y = 512;
}
GUI::~GUI() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

void GUI::render() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  {
    ImGui::Begin("Debug");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate,
                io->Framerate);

    if (ImGui::IsMousePosValid())
      ImGui::Text("Mouse pos: (%g, %g)", io->MousePos.x, io->MousePos.y);
    else
      ImGui::Text("Mouse pos: <INVALID>");
    ImGui::Text("Mouse delta: (%g, %g)", io->MouseDelta.x, io->MouseDelta.y);
    ImGui::Text("Mouse down:");
    for (int i = 0; i < IM_ARRAYSIZE(io->MouseDown); i++)
      if (ImGui::IsMouseDown(i)) {
        ImGui::SameLine();
        ImGui::Text("b%d (%.02f secs)", i, io->MouseDownDuration[i]);
      }
    ImGui::Text("Mouse wheel: %.1f", io->MouseWheel);
    ImGui::Text("io->WantCaptureMouse: %d", io->WantCaptureMouse);
    ImGui::Text("io->WantCaptureMouseUnlessPopupClose: %d", io->WantCaptureMouseUnlessPopupClose);
    ImGui::Text("io->WantCaptureKeyboard: %d", io->WantCaptureKeyboard);
    ImGui::Text("io->WantTextInput: %d", io->WantTextInput);
    ImGui::Text("io->WantSetMousePos: %d", io->WantSetMousePos);
    ImGui::Text("io->NavActive: %d, io->NavVisible: %d", io->NavActive, io->NavVisible);
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
    

    bool onCanvas = ImGui::IsWindowHovered();
    bool mouseDown = ImGui::IsMouseDown(ImGuiMouseButton_Left);
    
    bool draw = onCanvas && mouseDown;

    ImVec2 mousePosition;
    
    if (io->WantCaptureMouse) {
      mousePosition.x = ImGui::GetMousePos().x - ImGui::GetWindowPos().x;
      mousePosition.y = ImGui::GetMousePos().y - ImGui::GetWindowPos().y;
    }

    m_computeShader->bind();
    glUniform2f(0, mousePosition.x, mousePosition.y);
    glUniform4f(1, brushColour.x, brushColour.y, brushColour.z, brushColour.w);
    glUniform1i(2, clear ? 1 : 0);
    glUniform4f(3, clearColour.x, clearColour.y, clearColour.z, clearColour.w);

    if ((clear || draw)) {
      m_computeShader->bind();

      glBindImageTexture(0, m_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

      glDispatchCompute(canvasSize.x, canvasSize.y, 1);
      glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
      clear = false;
    }

    ImGui::Image((void *)(intptr_t)m_texture, canvasSize);
    ImGui::End();
    ImGui::PopStyleVar();
  }
  // Rendering
  ImGui::Render();
  glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    SDL_Window *backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
  }
}
} // namespace RGE