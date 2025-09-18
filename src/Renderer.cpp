#include <src/CanvasState.h>
#include <src/GUI.h>
#include <src/Renderer.h>

namespace RGE {
Renderer::Renderer(SDL_Window *window, std::shared_ptr<RGE::Shader> shader, uint32_t texture, CanvasState &state)
    : m_shader(std::move(shader)), m_texture(texture) {

  float vertices[] = {// pos        // uv
                      -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  -1.0f, 1.0f, 0.0f,
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

  // Renderer.cpp (end of constructor, after glTexImage2D and before state.clear=true)
  glGenFramebuffers(1, &m_FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    throw std::runtime_error("Framebuffer not complete");
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  // Optional: depth test off (we don’t use depth)
  glDisable(GL_DEPTH_TEST);

  state.clear = true;

  state.clear = true;
}

Renderer::~Renderer() {}

void Renderer::setClearColour(CanvasState &state) {
  glClearColor(state.clear_color.x * state.clear_color.w, state.clear_color.y * state.clear_color.w,
               state.clear_color.z * state.clear_color.w, state.clear_color.w);
}

void Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::renderCanvas(CanvasState &state) {
  if (!state.draw)
    return;

  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
  glViewport(0, 0, (GLint)state.canvasSize.x, (GLint)state.canvasSize.y);

  float brushSize = 8.0f;

  m_shader->bind();
  glUniform2f(0, state.mousePosition.x, state.mousePosition.y);
  glUniform4f(1, state.brushColour.x, state.brushColour.y, state.brushColour.z, state.brushColour.w);
  glUniform1i(2, state.clear ? 1 : 0);
  glUniform4f(3, state.clearColour.x, state.clearColour.y, state.clearColour.z, state.clearColour.w);
  glUniform1f(4, brushSize);
  glUniform2f(5, state.canvasSize.x, state.canvasSize.y);

  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::clearCanvas(CanvasState &state) {
  if (!state.clear)
    return;

  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
  glViewport(0, 0, (GLint)state.canvasSize.x, (GLint)state.canvasSize.y);
  m_shader->bind();
  glUniform1i(2, 1);
  glUniform4f(3, state.clearColour.x, state.clearColour.y, state.clearColour.z, state.clearColour.w);

  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  state.clear = false; // consume one-shot
}

} // namespace RGE