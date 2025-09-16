#pragma once

#include <src/RGE_pch.h>
#include <src/CanvasState.h>
#include <src/ComputeShader.h>

namespace RGE {

class Renderer {
  public:
  Renderer(SDL_Window *window, std::shared_ptr<RGE::ComputeShader> computeShader, uint32_t texture, CanvasState &state);
  ~Renderer();

  void setClearColour(CanvasState &state);
  void clear();
  void renderCanvas(CanvasState &state);
  void clearCanvas(CanvasState & state); 
  uint32_t texture() const { return m_texture; }

  private:
  uint32_t m_texture;

  std::shared_ptr<RGE::ComputeShader> m_computeShader;

};
} // namespace RGE