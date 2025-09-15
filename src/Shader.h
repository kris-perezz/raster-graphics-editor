#include <iostream>
#include <string>

#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


#include <SDL3/SDL.h>

#include <glad/gl.h>





class Shader {
  public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

    void bind() const;
    void unBind() const;

  private:
    uint32_t m_rendererID;
};
