#include <memory>
#include <vector>
#include <string>
#include "Component.h"
namespace olivera
{
  class ShaderProgram;

  class Materials :public Component
  {
  public:

    void onInitialise(std::string _shader);

  private:

    std::shared_ptr<ShaderProgram> shader;
  };



}