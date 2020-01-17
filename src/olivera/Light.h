#include <memory>
#include <vector>
#include <string>
#include "Component.h"
#include <glm/glm.hpp>
namespace olivera
{
  class Entity;
  class ShaderProgram;

  struct Attenuation
  {
    float constant;
    float linear;
    float quadratic;
  };

  /**
  *Component derived class to set up lighting for object
  */
  class Light :public Component
  {
  public:
    /**
    *\Updates light set lights location
    */
    void onTick();
    /**
    *\Initialise lights
    */
    void onInitialise(std::string _shader, std::vector<std::shared_ptr<Entity>> &_entitiesOther);


    void setLightColor(glm::vec3 _lightColor);
    void setDiffuseColor(glm::vec3 _diffuseColor);
    void setAmbientColor(glm::vec3 _ambientColor);
    void setSpecularColor(glm::vec3 _specularColor);
    void setAttenuation(float _constant,float _linear,  float _quadratic);
  private:

    std::weak_ptr<ShaderProgram> shader;///<Weak Refrence to shader program
    std::vector<std::weak_ptr<Entity>> entitiesOther;///< vector of weak pointers to entites that will be light sources
    
    glm::vec3 lightColor;
    glm::vec3 diffuseColor;
    glm::vec3 ambientColor;
    glm::vec3 specularColor;
    Attenuation attenuationValues;
    
  };



}