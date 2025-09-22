#include <src/CanvasState.h>
#include <src/ComputeRenderer.h>
#include <src/GUI.h>

namespace RAGE {
ComputeRenderer::ComputeRenderer(SDL_Window *window,
                                 std::shared_ptr<RAGE::ComputeShader> computeShader,
                                 uint32_t texture, CanvasState &state)
    : m_computeShader(std::move(computeShader)), m_texture(texture) {

  if (m_texture == 0)
    glGenTextures(1, &m_texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, state.canvasSize.x, state.canvasSize.y, 0, GL_RGBA,
               GL_FLOAT, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);
  state.clear = true;
}

ComputeRenderer::~ComputeRenderer() {}

void ComputeRenderer::setClearColour(CanvasState &state) {
  glClearColor(state.clear_color.x * state.clear_color.w, state.clear_color.y * state.clear_color.w,
               state.clear_color.z * state.clear_color.w, state.clear_color.w);
}

void ComputeRenderer::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void ComputeRenderer::renderCanvas(CanvasState &state) {
  if (!state.draw)
    return;

  m_computeShader->bind();
  glUniform2f(0, state.mousePosition.x, state.mousePosition.y);
  glUniform4f(1, state.brushColour.x, state.brushColour.y, state.brushColour.z,
              state.brushColour.w);
  glUniform1i(2, state.clear ? 1 : 0);
  glUniform4f(3, state.clearColour.x, state.clearColour.y, state.clearColour.z,
              state.clearColour.w);

  glBindImageTexture(0, m_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
  glDispatchCompute(state.canvasSize.x, state.canvasSize.y, 1);
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
}

void ComputeRenderer::clearCanvas(CanvasState &state) {
  if (!state.clear)
    return;

  m_computeShader->bind();
  glUniform1i(2, 1);
  glUniform4f(3, state.clearColour.x, state.clearColour.y, state.clearColour.z,
              state.clearColour.w);

  glBindImageTexture(0, m_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

  glDispatchCompute(state.canvasSize.x, state.canvasSize.y, 1); // local_size=1,1,1
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);

  state.clear = false; // consume one-shot
}

} // namespace RAGE