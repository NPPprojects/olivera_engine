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

      /*****************************************************************************
      @brief Update an object's lighting based on the location of the light source
      lighting it.

      ******************************************************************************/
        void onTick();

      /**************************
      @brief Initialise lights

      ***************************/
        void onInitialise(std::string _shader, std::vector<std::shared_ptr<Entity>> &_entitiesOther);

      /**************************
      @brief Explanation

      ***************************/
        void setLightColor(glm::vec3 _lightColor);

      /**************************
      @brief Explanation

      ***************************/
        void setDiffuseColor(glm::vec3 _diffuseColor);

      /**************************
      @brief Explanation

      ***************************/
        void setAmbientColor(glm::vec3 _ambientColor);

      /**************************
      @brief Explanation

      ***************************/
        void setSpecularColor(glm::vec3 _specularColor);

      /**************************
      @brief Explanation

      ***************************/
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