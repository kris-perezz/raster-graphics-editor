#include <src/Style.h>

namespace RAGE {
void styleSetup() {
  ImGuiStyle &style = ImGui::GetStyle();

  ImVec4 *colors = style.Colors;

  // Base reds
  ImVec4 colPrimary = ImVec4(0xED / 255.0f, 0x49 / 255.0f, 0x54 / 255.0f, 1.0f);       // #ED4954
  ImVec4 colPrimaryHover = ImVec4(0xF6 / 255.0f, 0x47 / 255.0f, 0x53 / 255.0f, 1.0f);  // #F64753
  ImVec4 colPrimaryActive = ImVec4(0xD5 / 255.0f, 0x2F / 255.0f, 0x3F / 255.0f, 1.0f); // #D52F3F
  ImVec4 colPrimaryAlt = ImVec4(0x99 / 255.0f, 0x24 / 255.0f, 0x31 / 255.0f, 1.0f);    // #992431

  // Backgrounds
  ImVec4 colBgDark = ImVec4(0x0E / 255.0f, 0x12 / 255.0f, 0x15 / 255.0f, 1.0f); // #0E1215
  ImVec4 colBg = ImVec4(0x10 / 255.0f, 0x12 / 255.0f, 0x15 / 255.0f, 1.0f);     // #101215
  ImVec4 colBgAlt = ImVec4(0x1E / 255.0f, 0x23 / 255.0f, 0x27 / 255.0f, 1.0f);  // #1E2327

  // Text
  colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  colors[ImGuiCol_TextDisabled] = colPrimaryActive;
  colors[ImGuiCol_TextLink] = colPrimary;
  colors[ImGuiCol_TextSelectedBg] = colPrimaryAlt;

  // Windows / Popups
  colors[ImGuiCol_WindowBg] = colBgDark;
  colors[ImGuiCol_ChildBg] = colBg;
  colors[ImGuiCol_PopupBg] = colBg;
  colors[ImGuiCol_MenuBarBg] = colBg;
  colors[ImGuiCol_Border] = colBgAlt;
  colors[ImGuiCol_BorderShadow] = colBgDark;

  // Frames
  colors[ImGuiCol_FrameBg] = colBgAlt;
  colors[ImGuiCol_FrameBgHovered] = colPrimaryHover;
  colors[ImGuiCol_FrameBgActive] = colPrimary;

  // Titles
  colors[ImGuiCol_TitleBg] = colBgDark;
  colors[ImGuiCol_TitleBgActive] = colBg;
  colors[ImGuiCol_TitleBgCollapsed] = colBgDark;

  // Scrollbars
  colors[ImGuiCol_ScrollbarBg] = colBgDark;
  colors[ImGuiCol_ScrollbarGrab] = colBgAlt;
  colors[ImGuiCol_ScrollbarGrabHovered] = colPrimaryHover;
  colors[ImGuiCol_ScrollbarGrabActive] = colPrimary;

  // Checks / Sliders
  colors[ImGuiCol_CheckMark] = colPrimary;
  colors[ImGuiCol_SliderGrab] = colPrimary;
  colors[ImGuiCol_SliderGrabActive] = colPrimaryHover;

  // Buttons
  colors[ImGuiCol_Button] = colPrimary;
  colors[ImGuiCol_ButtonHovered] = colPrimaryHover;
  colors[ImGuiCol_ButtonActive] = colPrimaryActive;

  // Headers
  colors[ImGuiCol_Header] = colBgAlt;
  colors[ImGuiCol_HeaderHovered] = colPrimary;
  colors[ImGuiCol_HeaderActive] = colPrimaryHover;

  // Separators
  colors[ImGuiCol_Separator] = colBgAlt;
  colors[ImGuiCol_SeparatorHovered] = colPrimaryHover;
  colors[ImGuiCol_SeparatorActive] = colPrimary;

  // Resize grips
  colors[ImGuiCol_ResizeGrip] = colBgAlt;
  colors[ImGuiCol_ResizeGripHovered] = colPrimaryHover;
  colors[ImGuiCol_ResizeGripActive] = colPrimary;

  // Input cursor
  colors[ImGuiCol_InputTextCursor] = colPrimaryHover;

  // Tabs
  colors[ImGuiCol_Tab] = colBgAlt;
  colors[ImGuiCol_TabHovered] = colPrimary;
  colors[ImGuiCol_TabSelected] = colPrimaryHover;
  colors[ImGuiCol_TabSelectedOverline] = colPrimary;
  colors[ImGuiCol_TabDimmed] = colBgAlt;
  colors[ImGuiCol_TabDimmedSelected] = colPrimaryAlt;
  colors[ImGuiCol_TabDimmedSelectedOverline] = colPrimary;

  // Docking
  colors[ImGuiCol_DockingPreview] = colPrimaryHover;
  colors[ImGuiCol_DockingEmptyBg] = colBgDark;

  // Plots
  colors[ImGuiCol_PlotLines] = colPrimary;
  colors[ImGuiCol_PlotLinesHovered] = colPrimaryHover;
  colors[ImGuiCol_PlotHistogram] = colPrimaryActive;
  colors[ImGuiCol_PlotHistogramHovered] = colPrimaryHover;

  // Tables
  colors[ImGuiCol_TableHeaderBg] = colBgAlt;
  colors[ImGuiCol_TableBorderStrong] = colBg;
  colors[ImGuiCol_TableBorderLight] = colBgAlt;
  colors[ImGuiCol_TableRowBg] = colBgDark;
  colors[ImGuiCol_TableRowBgAlt] = colBg;

  // Misc
  colors[ImGuiCol_TreeLines] = colBgAlt;
  colors[ImGuiCol_DragDropTarget] = colPrimaryHover;
  colors[ImGuiCol_NavCursor] = colPrimary;
  colors[ImGuiCol_NavWindowingHighlight] = colPrimaryHover;
  colors[ImGuiCol_NavWindowingDimBg] = colBgDark;
  colors[ImGuiCol_ModalWindowDimBg] = colBg;
}

void styleSetup1() {
  ImGuiStyle &style = ImGui::GetStyle();
  ImVec4 *colors = style.Colors;

  // Reds
  ImVec4 colPrimary = ImVec4(0xED / 255.0f, 0x49 / 255.0f, 0x54 / 255.0f, 1.0f);       // #ED4954
  ImVec4 colPrimaryHover = ImVec4(0xF6 / 255.0f, 0x47 / 255.0f, 0x53 / 255.0f, 1.0f);  // #F64753
  ImVec4 colPrimaryActive = ImVec4(0xD5 / 255.0f, 0x2F / 255.0f, 0x3F / 255.0f, 1.0f); // #D52F3F
  ImVec4 colPrimaryAlt = ImVec4(0x99 / 255.0f, 0x24 / 255.0f, 0x31 / 255.0f, 1.0f);    // #992431

  // Base UI
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
  colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

  // Frames
  colors[ImGuiCol_FrameBg] = ImVec4(colPrimaryAlt.x, colPrimaryAlt.y, colPrimaryAlt.z, 0.54f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 0.40f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(colPrimaryActive.x, colPrimaryActive.y, colPrimaryActive.z, 0.67f);

  // Titles
  colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = colPrimaryAlt;
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);

  // Scrollbars
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = colPrimaryHover;
  colors[ImGuiCol_ScrollbarGrabActive] = colPrimaryActive;

  // Checks / Sliders
  colors[ImGuiCol_CheckMark] = colPrimary;
  colors[ImGuiCol_SliderGrab] = colPrimary;
  colors[ImGuiCol_SliderGrabActive] = colPrimaryActive;

  // Buttons
  colors[ImGuiCol_Button] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 0.40f);
  colors[ImGuiCol_ButtonHovered] = colPrimaryHover;
  colors[ImGuiCol_ButtonActive] = colPrimaryActive;

  // Headers
  colors[ImGuiCol_Header] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 0.31f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 0.80f);
  colors[ImGuiCol_HeaderActive] = colPrimaryActive;

  // Separators
  colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
  colors[ImGuiCol_SeparatorHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 0.78f);
  colors[ImGuiCol_SeparatorActive] = colPrimaryActive;

  // Resize grips
  colors[ImGuiCol_ResizeGrip] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 0.20f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(colPrimaryActive.x, colPrimaryActive.y, colPrimaryActive.z, 0.95f);

  // Text cursor
  colors[ImGuiCol_InputTextCursor] = colors[ImGuiCol_Text];

  // Tabs
  colors[ImGuiCol_Tab] = colPrimaryAlt;
  colors[ImGuiCol_TabHovered] = colPrimaryHover;
  colors[ImGuiCol_TabSelected] = colPrimary;
  colors[ImGuiCol_TabSelectedOverline] = colPrimaryHover;
  colors[ImGuiCol_TabDimmed] = colPrimaryAlt;
  colors[ImGuiCol_TabDimmedSelected] = colPrimaryActive;
  colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 0.00f);

  // Docking
  colors[ImGuiCol_DockingPreview] = ImVec4(colPrimaryActive.x, colPrimaryActive.y, colPrimaryActive.z, 0.70f);
  colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

  // Plots
  colors[ImGuiCol_PlotLines] = colPrimary;
  colors[ImGuiCol_PlotLinesHovered] = colPrimaryHover;
  colors[ImGuiCol_PlotHistogram] = colPrimaryActive;
  colors[ImGuiCol_PlotHistogramHovered] = colPrimaryHover;

  // Tables
  colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
  colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
  colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
  colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);

  // Misc
  colors[ImGuiCol_TreeLines] = colors[ImGuiCol_Border];
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavCursor] = colPrimary;
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void styleSetup2() {
  ImGuiStyle &style = ImGui::GetStyle();
  ImVec4 *colors = style.Colors;

  style.Alpha = 1.0f;
  style.DisabledAlpha = 1.0f;
  style.WindowPadding = ImVec2(12.0f, 12.0f);
  style.WindowRounding = 11.5f;
  style.WindowBorderSize = 0.0f;
  style.WindowMinSize = ImVec2(20.0f, 20.0f);
  style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
  style.WindowMenuButtonPosition = ImGuiDir_Right;
  style.ChildRounding = 0.0f;
  style.ChildBorderSize = 1.0f;
  style.PopupRounding = 0.0f;
  style.PopupBorderSize = 1.0f;
  style.FramePadding = ImVec2(20.0f, 3.400000095367432f);
  style.FrameRounding = 11.89999961853027f;
  style.FrameBorderSize = 0.0f;
  style.ColumnsMinSpacing = 4.900000095367432f;
  style.ScrollbarSize = 11.60000038146973f;
  style.ScrollbarRounding = 15.89999961853027f;
  style.GrabMinSize = 3.700000047683716f;
  style.GrabRounding = 20.0f;
  style.TabRounding = 0.0f;
  style.TabBorderSize = 2.0f;
  style.ColorButtonPosition = ImGuiDir_Right;
  style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
  style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

  // Base reds
  ImVec4 colPrimary = ImVec4(0xED / 255.0f, 0x49 / 255.0f, 0x54 / 255.0f, 1.0f);       // rgba(237, 73, 84, 1)
  ImVec4 colPrimaryHover = ImVec4(0xF6 / 255.0f, 0x47 / 255.0f, 0x53 / 255.0f, 1.0f);  // rgba(246, 71, 83, 1)
  ImVec4 colPrimaryActive = ImVec4(0xD5 / 255.0f, 0x2F / 255.0f, 0x3F / 255.0f, 1.0f); // rgba(213, 47, 63, 1)
  ImVec4 colPrimaryAlt = ImVec4(0x99 / 255.0f, 0x24 / 255.0f, 0x31 / 255.0f, 1.0f);    // rgba(153, 36, 49, 1)

  // Backgrounds
  ImVec4 colBgDark = ImVec4(0x0E / 255.0f, 0x12 / 255.0f, 0x15 / 255.0f, 1.0f); // #0E1215
  ImVec4 colBg = ImVec4(0x10 / 255.0f, 0x12 / 255.0f, 0x15 / 255.0f, 1.0f);     // #101215
  ImVec4 colBgAlt = ImVec4(0x1E / 255.0f, 0x23 / 255.0f, 0x27 / 255.0f, 1.0f);  // #1E2327

  // Text
  colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  colors[ImGuiCol_TextDisabled] = ImVec4(colPrimaryActive.x, colPrimaryActive.y, colPrimaryActive.z, 1.0f);
  colors[ImGuiCol_TextLink] = colPrimary;
  colors[ImGuiCol_TextSelectedBg] = ImVec4(colPrimaryAlt.x, colPrimaryAlt.y, colPrimaryAlt.z, 1.0f);

  // Windows / Popups
  colors[ImGuiCol_WindowBg] = ImVec4(colBgDark.x, colBgDark.y, colBgDark.z, 0.94f);
  colors[ImGuiCol_ChildBg] = ImVec4(colBg.x, colBg.y, colBg.z, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(colBg.x, colBg.y, colBg.z, 0.94f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(colBg.x, colBg.y, colBg.z, 1.0f);
  colors[ImGuiCol_Border] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 0.50f);
  colors[ImGuiCol_BorderShadow] = ImVec4(colBgDark.x, colBgDark.y, colBgDark.z, 0.00f);

  // Frames
  colors[ImGuiCol_FrameBg] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 0.54f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 0.40f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 0.67f);

  // Titles
  colors[ImGuiCol_TitleBg] = ImVec4(colBgDark.x, colBgDark.y, colBgDark.z, 1.0f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(colBg.x, colBg.y, colBg.z, 1.0f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(colBgDark.x, colBgDark.y, colBgDark.z, 0.51f);

  // Scrollbars
  colors[ImGuiCol_ScrollbarBg] = ImVec4(colBgDark.x, colBgDark.y, colBgDark.z, 0.53f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 1.0f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 1.0f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 1.0f);

  // Checks / Sliders
  colors[ImGuiCol_CheckMark] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 1.0f);
  colors[ImGuiCol_SliderGrab] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 1.0f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 1.0f);

  // Buttons
  colors[ImGuiCol_Button] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 0.40f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 1.0f);
  colors[ImGuiCol_ButtonActive] = ImVec4(colPrimaryActive.x, colPrimaryActive.y, colPrimaryActive.z, 1.0f);

  // Headers
  colors[ImGuiCol_Header] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 0.31f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 0.80f);
  colors[ImGuiCol_HeaderActive] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 1.0f);

  // Separators
  colors[ImGuiCol_Separator] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 0.50f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 0.78f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 1.0f);

  // Resize grips
  colors[ImGuiCol_ResizeGrip] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 0.20f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 0.95f);

  // Input cursor
  colors[ImGuiCol_InputTextCursor] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 1.0f);

  // Tabs
  colors[ImGuiCol_Tab] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 1.0f);
  colors[ImGuiCol_TabHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 1.0f);
  colors[ImGuiCol_TabSelected] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 1.0f);
  colors[ImGuiCol_TabSelectedOverline] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 1.0f);
  colors[ImGuiCol_TabDimmed] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 1.0f);
  colors[ImGuiCol_TabDimmedSelected] = ImVec4(colPrimaryAlt.x, colPrimaryAlt.y, colPrimaryAlt.z, 1.0f);
  colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 0.00f);

  // Docking
  colors[ImGuiCol_DockingPreview] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 0.70f);
  colors[ImGuiCol_DockingEmptyBg] = ImVec4(colBgDark.x, colBgDark.y, colBgDark.z, 1.0f);

  // Plots
  colors[ImGuiCol_PlotLines] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 1.0f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 1.0f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(colPrimaryActive.x, colPrimaryActive.y, colPrimaryActive.z, 1.0f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 1.0f);

  // Tables
  colors[ImGuiCol_TableHeaderBg] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 1.0f);
  colors[ImGuiCol_TableBorderStrong] = ImVec4(colBg.x, colBg.y, colBg.z, 1.0f);
  colors[ImGuiCol_TableBorderLight] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 1.0f);
  colors[ImGuiCol_TableRowBg] = ImVec4(colBgDark.x, colBgDark.y, colBgDark.z, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(colBg.x, colBg.y, colBg.z, 0.06f);

  // Misc
  colors[ImGuiCol_TreeLines] = ImVec4(colBgAlt.x, colBgAlt.y, colBgAlt.z, 0.50f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(colPrimaryHover.x, colPrimaryHover.y, colPrimaryHover.z, 0.90f);
  colors[ImGuiCol_NavCursor] = ImVec4(colPrimary.x, colPrimary.y, colPrimary.z, 1.0f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0, 0, 0, 0.6f);
}

void styleSetup3() {
  ImGuiStyle &style = ImGui::GetStyle();

  style.Alpha = 1.0f;
  style.DisabledAlpha = 1.0f;
  style.WindowPadding = ImVec2(12.0f, 12.0f);
  style.WindowRounding = 11.5f;
  style.WindowBorderSize = 0.0f;
  style.WindowMinSize = ImVec2(20.0f, 20.0f);
  style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
  style.WindowMenuButtonPosition = ImGuiDir_Right;
  style.ChildRounding = 0.0f;
  style.ChildBorderSize = 1.0f;
  style.PopupRounding = 0.0f;
  style.PopupBorderSize = 1.0f;
  style.FramePadding = ImVec2(20.0f, 3.400000095367432f);
  style.FrameRounding = 11.89999961853027f;
  style.FrameBorderSize = 0.0f;
  style.ItemSpacing = ImVec2(4.300000190734863f, 5.5f);
  style.ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
  style.CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
  style.IndentSpacing = 0.0f;
  style.ColumnsMinSpacing = 4.900000095367432f;
  style.ScrollbarSize = 11.60000038146973f;
  style.ScrollbarRounding = 15.89999961853027f;
  style.GrabMinSize = 3.700000047683716f;
  style.GrabRounding = 20.0f;
  style.TabRounding = 0.0f;
  style.TabBorderSize = 0.0f;
  style.ColorButtonPosition = ImGuiDir_Right;
  style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
  style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

  style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
  style.Colors[ImGuiCol_ChildBg] = ImVec4(0.09250493347644806f, 0.100297249853611f, 0.1158798336982727f, 1.0f);
  style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
  style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
  style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
  style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1120669096708298f, 0.1262156516313553f, 0.1545064449310303f, 1.0f);
  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
  style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
  style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
  style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
  style.Colors[ImGuiCol_TitleBgCollapsed] =
      ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
  style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered] =
      ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrabActive] =
      ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
  style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
  style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.971993625164032f, 1.0f, 0.4980392456054688f, 1.0f);
  style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.7953379154205322f, 0.4980392456054688f, 1.0f);
  style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1821731775999069f, 0.1897992044687271f, 0.1974248886108398f, 1.0f);
  style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1545050293207169f, 0.1545048952102661f, 0.1545064449310303f, 1.0f);
  style.Colors[ImGuiCol_Header] = ImVec4(0.1414651423692703f, 0.1629818230867386f, 0.2060086131095886f, 1.0f);
  style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1072951927781105f, 0.107295036315918f, 0.1072961091995239f, 1.0f);
  style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
  style.Colors[ImGuiCol_Separator] = ImVec4(0.1293079704046249f, 0.1479243338108063f, 0.1931330561637878f, 1.0f);
  style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
  style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
  style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1459212601184845f, 0.1459220051765442f, 0.1459227204322815f, 1.0f);
  style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
  style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.999999463558197f, 1.0f, 0.9999899864196777f, 1.0f);
  style.Colors[ImGuiCol_Tab] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
  style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
  style.Colors[ImGuiCol_TabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
  style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
  style.Colors[ImGuiCol_TabUnfocusedActive] =
      ImVec4(0.1249424293637276f, 0.2735691666603088f, 0.5708154439926147f, 1.0f);
  style.Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
  style.Colors[ImGuiCol_PlotLinesHovered] =
      ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
  style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8841201663017273f, 0.7941429018974304f, 0.5615870356559753f, 1.0f);
  style.Colors[ImGuiCol_PlotHistogramHovered] =
      ImVec4(0.9570815563201904f, 0.9570719599723816f, 0.9570761322975159f, 1.0f);
  style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
  style.Colors[ImGuiCol_TableBorderStrong] =
      ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
  style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
  style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
  style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
  style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9356134533882141f, 0.9356129765510559f, 0.9356223344802856f, 1.0f);
  style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
  style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.266094446182251f, 0.2890366911888123f, 1.0f, 1.0f);
  style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
  style.Colors[ImGuiCol_NavWindowingDimBg] =
      ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
  style.Colors[ImGuiCol_ModalWindowDimBg] =
      ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
}
void styleSetup4() {
  // RAGE2 style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();
	
	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.5f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 0.0f;
	style.TabBorderSize = 0.0f;
	//style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
	
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);

	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.02745098061859608f, 0.03529411926865578f, 0.04313725605607033f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.05490196123719215f, 0.07058823853731155f, 0.08235294371843338f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.02745098061859608f, 0.03529411926865578f, 0.04313725605607033f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.003921568859368563f, 0.007843137718737125f, 0.007843137718737125f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.003921568859368563f, 0.007843137718737125f, 0.007843137718737125f, 0.6980392336845398f);

	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.05490196123719215f, 0.07058823853731155f, 0.08235294371843338f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2313725501298904f, 0.4980392158031464f);

	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.05490196123719215f, 0.07058823853731155f, 0.08235294371843338f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.01568627543747425f, 0.01960784383118153f, 0.0235294122248888f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05490196123719215f, 0.05490196123719215f, 0.05490196123719215f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 0.3450980484485626f);

  style.Colors[ImGuiCol_DockingPreview] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.529411792755127f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);

	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9058823585510254f, 0.1568627506494522f, 0.2196078449487686f, 1.0f);

	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	style.Colors[ImGuiCol_Button] = ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2313725501298904f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.05098039284348488f, 0.062745101749897f, 0.07450980693101883f, 1.0f);

	style.Colors[ImGuiCol_Header] = ImVec4(0.05098039284348488f, 0.062745101749897f, 0.07450980693101883f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2313725501298904f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.501960813999176f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.6695278882980347f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9570815563201904f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1019607856869698f, 0.1137254908680916f, 0.1294117718935013f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2039215713739395f, 0.2078431397676468f, 0.2156862765550613f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.3019607961177826f, 0.3019607961177826f, 0.3019607961177826f, 0.2000000029802322f);

	style.Colors[ImGuiCol_Tab] = ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2313725501298904f, 1.0f);
	style.Colors[ImGuiCol_TabSelected] = ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);
  style.Colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);
	style.Colors[ImGuiCol_TabDimmed] = ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 0.501960813999176f);
	style.Colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 0.501960813999176f);
  style.Colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 0.501960813999176f);
  
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2235294133424759f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);

	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.1882352977991104f, 0.196078434586525f, 0.2039215713739395f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2431372553110123f, 0.2549019753932953f, 0.2666666805744171f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.09803921729326248f, 0.01960784383118153f, 0.0235294122248888f, 0.05882352963089943f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.9960784316062927f, 0.9215686321258545f, 0.9215686321258545f, 0.05882352963089943f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9058823585510254f, 0.1568627506494522f, 0.2196078449487686f, 1.0f);

	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.9686274528503418f, 0.2784313857555389f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.1803921610116959f, 0.2274509817361832f, 0.2784313857555389f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.5450980663299561f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.3529411852359772f);
}
} // namespace RAGE