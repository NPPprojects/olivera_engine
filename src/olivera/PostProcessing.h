#include <memory>
#include "Component.h"

/********************************************************************
REMOVE HARDCODED SHADER UNIFORMS
Rename SquareMesh to RectangleMesh
*********************************************************************/

namespace olivera
{
  class Core;

  class ShaderProgram;
 
  class VertexArray;

  class CurrentCamera;
  
  /***********************************************************************
  @brief Post-Processing enabled by creating a 2D texture and outpitting 
  everything in the scene to it. enabling the user to add custom 
  Shader Programs for different post Processing effects.

  ************************************************************************/
  class PostProcessing
  {
    public:

    /*************************************************************************
    @brief Constructor for framebuffer that will be used for post-processing.

    @param std::shared_ptr<Core> core 
    @param std::string shader resource
    @param std::string mesh resource
    @param int width of window
    @param int height of window

    **************************************************************************/
      PostProcessing(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh, int _width, int _height);

 

    /**********************************************************
    @brief Assigns FBO, and all other needed configurations

    ***********************************************************/
      void FrameBufferConfiguration();

    /*********************
    @brief Getter for FBO
    **********************/
      int getFBO();
  
    /***********************************
    @brief bind framebuffer and draw it

    ************************************/
      void use();

    private:
    /**********************************************************************************************************************************/

      unsigned int FBO;                                                                                         //!<Frame Buffer Object
      unsigned int textureColorBuffer;                                                         //!<Texture color buffer for framebuffer
      unsigned int renderBuffer;                                                                               //!<Render buffer object


      int blurIntesity;                                                                        //!<Uniform values that i need to delete
      float exposure;
      float gamma;
      bool filter;

      int width;                                                                                                //!<Width of Framebuffer
      int height;                                                                                              //!<Height of Framebuffer


      std::weak_ptr<VertexArray> squareMesh;                                                       //!<Weak pointer to framebuffer mesh
      std::weak_ptr<ShaderProgram> shader;                                                            //!<Weak pointer to shader program
      std::weak_ptr<Core> core;                                                                                 //!<Weak pointer to core

    /**********************************************************************************************************************************/
  };


}