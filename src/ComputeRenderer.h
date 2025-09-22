#pragma once

#include <src/CanvasState.h>
#include <src/ComputeShader.h>
#include <src/RAGE_pch.h>

namespace RAGE {

class ComputeRenderer {
public:
  ComputeRenderer(SDL_Window *window, std::shared_ptr<RAGE::ComputeShader> computeShader,
                  uint32_t texture, CanvasState &state);
  ~ComputeRenderer();

  void setClearColour(CanvasState &state);
  void clear();
  void renderCanvas(CanvasState &state);
  void clearCanvas(CanvasState &state);
  uint32_t texture() const { return m_texture; }

private:
  uint32_t m_texture;

  std::shared_ptr<RAGE::ComputeShader> m_computeShader;
};
} // namespace RAGE