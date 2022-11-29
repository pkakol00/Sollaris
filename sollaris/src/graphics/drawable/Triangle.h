#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Drawable.h"

class Triangle: public Drawable {
  private:
    uint VAO, VBO, EBO;

    const static inline float vertices[] = {
       0.5f,  0.5f, 0.0f,  // top right
       0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f   // top left 
    };
    const static inline unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
    };  
   public:
    void draw() override;
    Triangle();
};

#endif // __TRIANGLE_H__