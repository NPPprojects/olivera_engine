#include <memory>
#include <vector>
#include <string>
#include "Component.h"
namespace olivera
{
  class ShaderProgram;
  /**
  *Component derived class to set up lighting for object
  */
  class Light :public Component
  {
  public:

    void onInitialise(std::string _shader);

  private:

    std::weak_ptr<ShaderProgram> shader;
  };



}