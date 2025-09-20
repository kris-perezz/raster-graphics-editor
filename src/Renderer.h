#pragma once

#include <stb/stb_image_write.h>
#include <src/CanvasState.h>
#include <src/RGE_pch.h>
#include <src/Shader.h>

namespace RGE {

class Renderer {
public:
  Renderer(SDL_Window *window, std::shared_ptr<RGE::Shader> shader, uint32_t texture, CanvasState &state);
  ~Renderer();

  void setClearColour(CanvasState &state);
  void clear();
  void renderCanvas(CanvasState &state);
  void clearCanvas(CanvasState &state);
  void saveImage(CanvasState &state);
  uint32_t texture() const { return m_texture; }

private:
  uint32_t m_texture;

  uint32_t m_VAO;
  uint32_t m_VBO;
  uint32_t m_EBO;
  uint32_t m_FBO;
  std::shared_ptr<RGE::Shader> m_shader;
};
} // namespace RGE