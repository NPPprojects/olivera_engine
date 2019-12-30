
#include "Component.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace olivera
{

  class Texture : public Component
  {
  public:

    int LoadTexture(const char* _path);
    glm::vec2 getSize();
    GLuint getId();
    void onDisplay();
    void onInitialise(const char* path);

  private:
    GLuint id;
    glm::vec2 size;


  };


}


