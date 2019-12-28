#include "Component.h"

#include <memory>

namespace olivera
{
class ShaderProgram;

class MeshRenderer : public Component
{
public:
  void onInitialise();

private:
  void onDisplay();

  std::shared_ptr<ShaderProgram> shader;


};

}
