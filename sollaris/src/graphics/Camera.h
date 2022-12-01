#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
  public:
    glm::vec3 position;
    glm::vec3 rotation;

    glm::mat4 getProjectionViewMatrix();

    Camera();    
  private:
};

#endif // __CAMERA_H__