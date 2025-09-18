#pragma once

#include <src/RGE_pch.h>

namespace RGE {
class Shader {
public:
  Shader(const char *vertexPath, const char *fragmentPath);
  ~Shader();

  void bind() const;
  void unBind() const;

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

private:
  uint32_t m_rendererID;
};
}