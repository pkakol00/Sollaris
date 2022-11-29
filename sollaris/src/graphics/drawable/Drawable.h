#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <util/Log.h>
#include <glm/glm.hpp>

class Drawable {
  protected:
  public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    virtual void draw() = 0;
    glm::mat4 getModelMatrix();
};

#endif // __DRAWABLE_H__