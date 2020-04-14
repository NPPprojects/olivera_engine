#include <memory>
#include "Component.h"

namespace olivera
{
  
  class Core;

  class ShaderProgram;
 
  class VertexBuffer;

  class CurrentCamera;
  
  /**
  * Post-Processing enabled by creating a 2D texture and outpitting everything in the scene to it enabling the user to add custom Shader Programs for different post Processing effects
  */
  class PostProcessing
  {
  public:

  /**
  *\ Constructor for post processing taking in the core in which it's contained, a Shader Program, and the mesh for it
 */
  PostProcessing(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh, int _width, int _height);

 

  /**
  *\ Configure frameBuffer
  */
    void FrameBufferConfiguration();

    /**
   *\ getter For FBO
   */
  int getFBO();
  
  /**
  *\ use framebuffer
  */
  void use();

  private:

    unsigned int FBO;///<FBO for framebuffer
    unsigned int textureColorBuffer;///<texture color buffer for framebuffer
    unsigned int renderBuffer;///<render buffer object


    int blurIntesity;///<uniform values that i need to delete
    float exposure;
    float gamma;
    bool filter;

    int width, height;


    std::weak_ptr<VertexBuffer> squareMesh;///<Weak pointer to square mesh 
    std::weak_ptr<ShaderProgram> shader;///<Weak pointer to shader program
    std::weak_ptr<Core> core;///<Weak pointer to the core in which the post processing framebuffer shader and square Mesh will be passed to
  };


}