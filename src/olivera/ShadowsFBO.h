
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

#include "Component.h"
namespace olivera
{
  /******************************************************************
  @brief Class to handle generating a DepthMap to create shadows

  *******************************************************************/
  class ShadowsFBO
  {
    public:

      /*****************************************************
      @brief Call OpenGL Methods to configure Framebuffer
      that will be used to create a depthMap.
      
      ******************************************************/
      void configureFBO();

      /******************************************************************
      @brief Assign shadowCubemap transformations using light positions

      *******************************************************************/
      void createCubemapTransformationMatrices(glm::vec3 _lightPos);

      /*****************************************************
      @brief Bind FBO, using shadow Resutiolon, and then 
      assign uniform values for shadow Matracies
      
      ******************************************************/
      void bindFBO(std::shared_ptr<ResourceManager> _resourceManager, std::string _shader);

      /****************************
      @brief Getter for near plane

      @return nearPlane

      *****************************/
       float getNearPlane();

      /****************************
      @brief Getter for far plane
                                 
      @return farPlane           

      *****************************/
        float getFarPlane();

      /********************************
      @brief Getter for Depth Cubemap
     
      @return depthCubemap
     
      *********************************/
        int getDepthCubemap();


    private:
      /********************************************************************************************************************/
     
      const unsigned int resolution = 2048;                                                         //</ Shadows Resolution

      unsigned int depthCubemap;                                                           //</ Texture CubeMap for Shadows
      unsigned int FBO;                                                                             //</ Framebuffer Object

      const float farPlane = 100.f;                                                              //</ Far plane for shadows
      const float nearPlane = 1.0f;                                                             //</ Near plane for shadpws

      std::vector<glm::mat4> shadowTransforms;                                    //</Vector to hold shadow Transformations

      /********************************************************************************************************************/

  };



}

