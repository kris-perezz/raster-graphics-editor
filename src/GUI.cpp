#include <ImGuiFileDialog/ImGuiFileDialog.h>
#include <src/GUI.h>
#include <src/Style.h>

namespace RAGE {
GUI::GUI(SDL_Window *window, SDL_GLContext context, float mainScale, const char *glslVersion, uint32_t texture)
    : m_texture(texture) {

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = &ImGui::GetIO();

  io->IniFilename = nullptr; // ignore saved positions

  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  // io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // Setup Dear ImGui style
  //ImGui::StyleColorsDark();

  ImGuiStyle &style = ImGui::GetStyle();
  styleSetup4();
  style.ScaleAllSizes(mainScale);
  style.FontScaleDpi = mainScale;
  const char *base = SDL_GetBasePath();
  std::string fontPath = std::string(base) + "data/AnonymousPro-Regular.ttf";
  io->Fonts->AddFontFromFileTTF(fontPath.c_str(), 14.0f);
  io->ConfigDpiScaleFonts = true;
  io->ConfigDpiScaleViewports = true;

  // Setup Platform/Renderer backends
  ImGui_ImplSDL3_InitForOpenGL(window, context);
  ImGui_ImplOpenGL3_Init(glslVersion);
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

  m_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(m_viewport->Pos);
  ImGui::SetNextWindowSize(m_viewport->Size);
  ImGui::SetNextWindowViewport(m_viewport->ID);

  ImGuiWindowFlags host_window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
  ImGui::Begin("MainDockSpace", nullptr,
               ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
                   ImGuiWindowFlags_NoNavFocus);

  ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

  ImGui::End();

  static bool first_time = true;
  if (first_time) {
    first_time = false;

    ImGui::DockBuilderRemoveNode(dockspace_id); // clear old layout
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id, m_viewport->Size);

    ImGuiID dock_main_id = dockspace_id;
    ImGuiID dock_left, dock_right;
    dock_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.25f, nullptr, &dock_main_id);
    dock_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);

    ImGui::DockBuilderDockWindow("Canvas", dock_main_id);
    ImGui::DockBuilderDockWindow("Debug", dock_right);
    ImGui::DockBuilderDockWindow("Raster Graphics Editor", dock_left);

    ImGui::DockBuilderFinish(dockspace_id);
  }
  {
    // ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    // ImGui::SetNextWindowSize(state.canvasSize, ImGuiCond_Once);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::Begin("Canvas", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);

    ImGui::Image((void *)(intptr_t)m_texture, state.canvasSize);

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
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

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
    // ImGui::SetNextWindowSize(ImVec2(512, 512), ImGuiCond_Once);
    ImGui::Begin("Raster Graphics Editor"); // Create a window called Raster
    // Graphics Editor
    static ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;

    // ImGui::ColorEdit3("clear color", (float *)&state.viewportColour);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::ColorPicker4("Canvas Colour", (float *)&state.canvasColour, base_flags | ImGuiColorEditFlags_DisplayRGB);

    if (ImGui::Button("Clear Canvas", ImVec2(200, 60))) {
      state.clear = true;
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::ColorPicker4("Brush Colour", (float *)&state.brushColour, base_flags | ImGuiColorEditFlags_DisplayRGB);
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    
    ImGui::DragFloat("Brush Size", &state.brushSize, 1.0f);

    if (ImGui::Button("Save Image", ImVec2(200, 60))) {
      const char *base = SDL_GetBasePath();
      IGFD::FileDialogConfig cfg;
      cfg.path = std::string(base); // starting directory
      cfg.fileName = "canvas.png";  // default file name
      cfg.flags = ImGuiFileDialogFlags_ConfirmOverwrite | ImGuiFileDialogFlags_DontShowHiddenFiles;

      ImGuiFileDialog::Instance()->OpenDialog("SavePNGDlg", "Save PNG", "PNG file{.png}", cfg);
    }
    {
      if (quitRequest) {
        ImGui::OpenPopup("RAGE Quit");
        quitRequest = false;
      }
      if (ImGui::BeginPopupModal("RAGE Quit", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Are you rage quitting?");
        if (ImGui::Button("Yes")) {
          quitConfirmed = true;
          ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("No")) {
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }
    }
    ImGui::End();
  }
  {
    ImVec2 minDialogueSize(m_viewport->Size.x * 0.8, m_viewport->Size.y * 0.4);
    ImVec2 maxDialogueSize(m_viewport->Size.x * 0.8, m_viewport->Size.y * 0.8);

    if (ImGuiFileDialog::Instance()->Display("SavePNGDlg", ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking,
                                             minDialogueSize, maxDialogueSize)) {
      if (ImGuiFileDialog::Instance()->IsOk()) {
        state.pendingSavePath = ImGuiFileDialog::Instance()->GetFilePathName();
        state.save = true;
      }
      ImGuiFileDialog::Instance()->Close();
    }
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
} // namespace RAGE