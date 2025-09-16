#include <src/ComputeShader.h>

namespace RGE {
ComputeShader::ComputeShader(const char *computePath) {
  std::string computeCode;
  std::ifstream cShaderFile;
  cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    cShaderFile.open(computePath);
    std::stringstream cShaderStream;

    cShaderStream << cShaderFile.rdbuf();

    cShaderFile.close();

    computeCode = cShaderStream.str();

  } catch (std::ifstream::failure e) {
    throw std::runtime_error("shader file read failed");
  }
  const char *cShaderCode = computeCode.c_str();

  uint32_t computeShader;

  computeShader = glCreateShader(GL_COMPUTE_SHADER);
  glShaderSource(computeShader, 1, &cShaderCode, nullptr);

  glCompileShader(computeShader);

  GLint isCompiled = 0;
  glGetShaderiv(computeShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(computeShader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(computeShader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(computeShader);

    return;
  }

  m_rendererID = glCreateProgram();
  GLuint program = m_rendererID;

  glAttachShader(program, computeShader);

  glLinkProgram(program);

  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    glDeleteProgram(program);

    glDeleteShader(computeShader);
    return;
  }

  glDetachShader(program, computeShader);
}

ComputeShader::~ComputeShader() { glDeleteProgram(m_rendererID); }

void ComputeShader::bind() const { glUseProgram(m_rendererID); }

void ComputeShader::unBind() const { glUseProgram(0); }

void ComputeShader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(m_rendererID, name.c_str()), (int)value);
}
void ComputeShader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(m_rendererID, name.c_str()), value);
}
void ComputeShader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_rendererID, name.c_str()), value);
}
}