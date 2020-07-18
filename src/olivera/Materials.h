#include <memory>
#include <vector>
#include <string>
#include "Component.h"
namespace olivera
  /********************************************************************
      NEED TO REWORK ENTIRE CLASS
  *********************************************************************/

{
  class ShaderProgram;

  class ResourceManager;

  /********************************************************
  @brief Hold all material related variables for an object.

  *********************************************************/
  struct Material 
  {
    float shininess;
    int diffuse;
    int specular;
  };

  /*****************************************************************
  @brief Set up material values for object
  
  *Further methods are implemented to add additional functunality.

  ******************************************************************/
  class Materials :public Component
  {
  public:
    /*******************************************************
    @brief Initialise default material values for an object

    @param std::string shader of the object

    ********************************************************/
      void onInitialise(std::string _shader, std::shared_ptr<olivera::ResourceManager> _objectResouces);

    /*******************************************************************
    @brief set new Material values.

    *Set modifications to true. This is done because normally
    Materials, need to be set only once. If setting them after the game 
    loop has started uniform values, need to be updated every tick.


    @param float shininess of the material
    @param int  diffuse color of the material
    @param int specular color of the materials

    ********************************************************************/
      void setMaterial(float _shininess, int _diffuse, int _specular);

    /*******************************************************************
    @brief set new Material values.

    *If materials won't change in the main loop, use this method, as
    values will get set for the shader only once instead of every tick.

    @param float shininess of the material
    @param int  diffuse color of the material
    @param int specular color of the materials

    ********************************************************************/
      void setDefaultMaterial(float _shininess, int _diffuse, int _specular);

    /******************************************************
    @brief Set uniform values for the shader, every frame.

    *Will only occur if setMaterial has been called.

    *******************************************************/
      void onTick();

  private:
  /********************************************************************************************************/

    std::weak_ptr<ShaderProgram> shader;                                        //!<Weak pointer to shader
   
    Material material;                                                   //!<Material values of the object
    
    bool modifications; //</ Set to true if the user wants to make changes to materials after onInitialise

  /********************************************************************************************************/
  };



}