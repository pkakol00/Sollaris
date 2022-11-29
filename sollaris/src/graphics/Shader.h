#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <glm/glm.hpp>

namespace ge {

class Shader {
  public:
    Shader(const std::string& file_path);
    Shader() = default;

    void bind();
    void unbind();

    void setUniformVec4(const std::string& name, glm::vec4);
    void setUniformMat4(const std::string& name, glm::mat4);

  private:
    uint shader_id;

    std::string readFromFile(const std::string& file_path);
    uint createShader(const std::string& file_path, uint type);
};

} // namespace ge

// TODO: destructor

#endif // __SHADER_H__