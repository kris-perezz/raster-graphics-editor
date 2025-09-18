#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_internal.h>
#include <src/GUI.h>

namespace RGE {
GUI::GUI(SDL_Window *window, SDL_GLContext context, float mainScale, const char *glslVersion,
         const std::shared_ptr<RGE::ComputeShader> computeShader, uint32_t texture)
    : m_computeShader(computeShader), m_texture(texture) {

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = &ImGui::GetIO();

  io->IniFilename = nullptr; // ignore saved positions

  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  // io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

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

  canvasSize.x = 512;
  canvasSize.y = 512;
}

GUI::~GUI() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

void GUI::render(CanvasState &state, uint32_t texture) {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);

  ImGuiWindowFlags host_window_flags =
      ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
      ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
  ImGui::Begin("MainDockSpace", nullptr,
               ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                   ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
                   ImGuiWindowFlags_NoNavFocus);

  ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

  ImGui::End();

  static bool first_time = true;
  if (first_time) {
    first_time = false;

    ImGui::DockBuilderRemoveNode(dockspace_id); // clear old layout
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

    ImGuiID dock_main_id = dockspace_id;
    ImGuiID dock_left, dock_right;
    dock_left =
        ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.25f, nullptr, &dock_main_id);
    dock_right =
        ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);

    ImGui::DockBuilderDockWindow("Canvas", dock_main_id);
    ImGui::DockBuilderDockWindow("Debug", dock_right);
    ImGui::DockBuilderDockWindow("Raster Graphics Editor", dock_left);

    ImGui::DockBuilderFinish(dockspace_id);
  }
  {
    // ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(canvasSize, ImGuiCond_Once);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::Begin("Canvas", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar |
                     ImGuiWindowFlags_NoMove);

    ImGui::Image((void *)(intptr_t)m_texture, canvasSize);

    bool onCanvas = ImGui::IsItemHovered();
    bool mouseDown = ImGui::IsMouseDown(ImGuiMouseButton_Left);

    state.draw = onCanvas && mouseDown;

    ImVec2 mousePosition;

    if (onCanvas) {
      const ImVec2 p0 = ImGui::GetItemRectMin();
      const ImVec2 mp = ImGui::GetIO().MousePos;
      state.mousePosition = {mp.x - p0.x, mp.y - p0.y};
    }

    ImGui::End();
    ImGui::PopStyleVar();
  }
  {
    // ImGui::SetNextWindowPos(ImVec2(0, 512), ImGuiCond_Once);
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
    // ImGui::SetNextWindowPos(ImVec2(512, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(512, 512), ImGuiCond_Once);
    ImGui::Begin("Raster Graphics Editor"); // Create a window called Raster
    // Graphics Editor

    ImGui::ColorEdit3("clear color",
                      (float *)&state.clear_color); // Edit 3 floats representing a color

    ImGui::ColorEdit3("Canvas Clear  Colour", (float *)&state.clearColour);

    static ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;
    ImGui::ColorPicker4("##picker", (float *)&state.brushColour,
                        base_flags | ImGuiColorEditFlags_DisplayRGB);

    if (ImGui::Button("Clear Canvas", ImVec2(200, 60))) {
      state.clear = true;
    }
    ImGui::End();
  }

  // Rendering
  ImGui::Render();
  glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
}
void GUI::draw() {
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