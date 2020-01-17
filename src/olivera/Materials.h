#include <memory>
#include <vector>
#include <string>
#include "Component.h"
namespace olivera
{
  class ShaderProgram;
  /**
  *Component derived class to set up material values for object
  */
  class Materials :public Component
  {
  public:
    /**
    *\Initialise  materials
    */
    void onInitialise(std::string _shader);

  private:

    std::weak_ptr<ShaderProgram> shader;///<weakPointer to lights
  };



}