#include <memory>
#include <vector>
#include <string>
#include "Component.h"
#include <glm/glm.hpp>
namespace olivera
  /********************************************************************
NEED TO REWORK CLASS
*********************************************************************/


{
  class ShaderProgram;
  
  class Entity;

  /***************************************************
  @brief Holds values to calculate light attenuation

  ****************************************************/
  struct Attenuation
  {
    float constant;
    float linear;
    float quadratic;
  };

  /************************************************************
  @brief Component derived class to set up lighting for object
  
  *************************************************************/
  class Light :public Component
  {
    public:

      /******************************************************************************
      @brief Update an object's lighting based on the location of the light source/s
      lighting it.

      *******************************************************************************/
        void onTick();

      /*********************************************************************************************
      @brief Add all entities to a list of light sources that affect the shader of the object.
      
      *Set up initial values for light color,diffuse, ambient, specular and all attenuation values.
      They can be further modified using the corresponding method.

      @param std::string _shader of the object
      @param std::vector<std::shared_ptr<Entity>> &Light Entitites

      **********************************************************************************************/
        void onInitialise(std::string _shader, std::vector<std::shared_ptr<Entity>> &_entitiesOther);

      /*****************************
      @brief Setter for lightColor

      @param glm::vec3 lightColor

      *****************************/
        void setLightColor(glm::vec3 _lightColor);

      /******************************
      @brief Setter for lightColor

      @param glm::vec3 difffuseColor

      *******************************/
        void setDiffuseColor(glm::vec3 _diffuseColor);

      /******************************
      @brief Setter for ambientColor

      @param glm::vec3 ambientColor
      *******************************/
        void setAmbientColor(glm::vec3 _ambientColor);

      /*******************************
      @brief Setter for specularColor

      @param glm::vec3 specularColor
      ********************************/
        void setSpecularColor(glm::vec3 _specularColor);

      /****************************
      @brief Setter for attenuation

      @param float constant
      @param float linear
      @param float quadratic
      *****************************/
        void setAttenuation(float _constant,float _linear,  float _quadratic);

    private:
    /************************************************************************************************************************/

      std::weak_ptr<ShaderProgram> shader;                                                //!<Weak Refrence to shader program
      std::vector<std::weak_ptr<Entity>> entitiesOther;    //!< vector of weak pointers to entites that will be light sources
    
      glm::vec3 lightColor;
      glm::vec3 diffuseColor;
      glm::vec3 ambientColor;
      glm::vec3 specularColor;
      Attenuation attenuationValues;
    
    /************************************************************************************************************************/
  };



}