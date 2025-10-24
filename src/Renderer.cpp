#include <include/stb/stb_image_write.h>

#include <src/CanvasState.h>
#include <src/GUI.h>
#include <src/Renderer.h>

namespace RAGE {
Renderer::Renderer(SDL_Window *window, std::shared_ptr<RAGE::Shader> shader, uint32_t texture, CanvasState &state)
    : m_shader(std::move(shader)), m_texture(texture) {

  float vertices[] = {-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  -1.0f, 1.0f, 0.0f,
                      1.0f,  1.0f,  1.0f, 1.0f, -1.0f, 1.0f,  0.0f, 1.0f};

  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  glGenVertexArrays(1, &m_VAO);

  glGenBuffers(1, &m_VBO);

  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(m_VAO);

  glBindVertexArray(0);

  if (m_texture == 0)
    glGenTextures(1, &m_texture);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, state.canvasSize.x, state.canvasSize.y, 0, GL_RGBA, GL_FLOAT, nullptr);

  glGenFramebuffers(1, &m_FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    throw std::runtime_error("Framebuffer not complete");
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_DEPTH_TEST);

  state.clear = true;
}

Renderer::~Renderer() {}

void Renderer::setClearColour(CanvasState &state) {
  glClearColor(state.viewportColour.x * state.viewportColour.w, state.viewportColour.y * state.viewportColour.w,
               state.viewportColour.z * state.viewportColour.w, state.viewportColour.w);
}

void Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::renderCanvas(CanvasState &state) {
  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
  glViewport(0, 0, (GLint)state.canvasSize.x, (GLint)state.canvasSize.y);

  if (state.draw) {
    m_shader->bind();
    glUniform2f(0, state.mousePosition.x, state.mousePosition.y);
    glUniform4f(1, state.brushColour.x, state.brushColour.y, state.brushColour.z, state.brushColour.w);
    glUniform1i(2, state.clear ? 1 : 0);
    glUniform4f(3, state.canvasColour.x, state.canvasColour.y, state.canvasColour.z, state.canvasColour.w);
    glUniform1f(4, state.brushSize);
    glUniform2f(5, state.canvasSize.x, state.canvasSize.y);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderBrushPreview(const CanvasState &state, const ImVec2 &canvasScreenPos,
                                  const ImVec2 &canvasScreenSize) {
  if (state.draw || state.mousePosition.x < 0) {
    return;
  }

  const ImVec2 windowSize = ImGui::GetIO().DisplaySize;
  int viewX = static_cast<int>(canvasScreenPos.x);
  int viewY = static_cast<int>(windowSize.y - canvasScreenPos.y - canvasScreenSize.y);

  float mouseY_bottom = state.canvasSize.y - state.mousePosition.y;
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(viewX, viewY, static_cast<GLint>(canvasScreenSize.x), static_cast<GLint>(canvasScreenSize.y));

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  m_shader->bind();
  glUniform2f(0, state.mousePosition.x, mouseY_bottom);
  glUniform4f(1, state.brushColour.x, state.brushColour.y, state.brushColour.z, state.brushColour.w);
  glUniform1i(2, 0);
  glUniform4f(3, state.canvasColour.x, state.canvasColour.y, state.canvasColour.z, state.canvasColour.w);
  glUniform1f(4, state.brushSize);
  glUniform2f(5, state.canvasSize.x, state.canvasSize.y);

  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
  glDisable(GL_BLEND);
  glViewport(0, 0, static_cast<GLint>(windowSize.x), static_cast<GLint>(windowSize.y));
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::clearCanvas(CanvasState &state) {
  if (!state.clear)
    return;

  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
  glViewport(0, 0, (GLint)state.canvasSize.x, (GLint)state.canvasSize.y);
  m_shader->bind();
  glUniform1i(2, 1);
  glUniform4f(3, state.canvasColour.x, state.canvasColour.y, state.canvasColour.z, state.canvasColour.w);

  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  state.clear = false; // consume one-shot
}

void Renderer::saveImage(CanvasState &state) {
  if (!state.save)
    return;
  const int w = static_cast<int>(state.canvasSize.x);
  const int h = static_cast<int>(state.canvasSize.y);
  if (w <= 0 || h <= 0)
    return;

  std::string outPath = state.pendingSavePath.empty() ? std::string("canvas.png") : state.pendingSavePath;

  glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FBO);
  glReadBuffer(GL_COLOR_ATTACHMENT0);

  GLint prev_pack = 0;
  glGetIntegerv(GL_PACK_ALIGNMENT, &prev_pack);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glPixelStorei(GL_PACK_ROW_LENGTH, 0);

  std::vector<unsigned char> rgba(static_cast<size_t>(w) * static_cast<size_t>(h) * 4u);
  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());

  stbi_flip_vertically_on_write(0);

  const int stride = w * 4;
  const int ok = stbi_write_png(outPath.c_str(), w, h, 4, rgba.data(), stride);

  glPixelStorei(GL_PACK_ALIGNMENT, prev_pack);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

  state.save = false;
  state.pendingSavePath.clear();
}

} // namespace RAGE