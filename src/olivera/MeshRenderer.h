
#include "Component.h"


#include <memory>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace olivera
{
class ShaderProgram;

class VertexBuffer;

class CurrentCamera;

class Core;

class Transform;

class Texture;

class Model;

  /*************************************************************************
  @brief Component derived class to handle drawing meshes to the screen.

  *Can currently handle .obj files and user defined using the .data format.

  **************************************************************************/
class MeshRenderer : public Component
{
public:
  /*************************************************************************
  @brief Initalisation for 3d models that are written in the .data format.

  *Loads

  @param std::vector<std::string> texturePaths a vector of loaded textures.

  @param std::string meshPath 

  @param std::string _shaderPath
  

  **************************************************************************/
    void onInitialise(std::vector<std::string> _texturePaths, std::string _meshPath, std::string _shaderPath);
  
  /*************************************************************
  @brief Initalisation for 3D models of .obj loaded with assimp

  *************************************************************/
    void onInitialise(std::string _modelPath, std::string _shaderPath);


  /************************************************
  @brief Draw function gets called every draw call

  *************************************************/
    void onDisplay();
  
  /****************************************************
  @brief Set projection,view and model matrix uniforms 
  every tick

  *****************************************************/
    void onTick();
  
  /**************************************************************
  @brief Draw function for drawing either .objs or .data objects
  
  ***************************************************************/
  void Draw();

private:

  /********************************************************************************************************************************************************************/
  std::vector<std::weak_ptr<Texture>> texture;                                //!< Vector for textures used by object defined by user(not .obj files,  but .data files)
 
 
  std::weak_ptr<CurrentCamera> cameraContext;                                                  //!< Weak pointer to the camera context so that it can display on screen
  std::weak_ptr<ShaderProgram> shader;                                                                                                      //!< Weak pointer to shader
  std::weak_ptr<VertexBuffer> object;                                                                                       //!< Weak pointer to mesh for .data objects
  std::weak_ptr<Transform> transform;                                                                                 //!< Weak pointer to entity's transform component
  std::weak_ptr<Entity> entitySelf;                                                                               //!< Weak pointer to entity this component belongs to
  std::weak_ptr<Model> model;                                                                            //!< Weak pointer pointing to .obj 3D model loaded with assimp
  std::weak_ptr<Core> core;                                                                                                                   //!< Weak pointer to core

  /********************************************************************************************************************************************************************/
};

}
