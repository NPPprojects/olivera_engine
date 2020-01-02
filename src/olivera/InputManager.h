#include "Component.h"
#include <memory>
namespace olivera
{

  class Keyboard;
  class Core;
  class Camera;

  class  InputManager : public Component
  {

  public:
    void CameraMovement();

    void onInitialise();

    void onTick();
 

  private:

    std::shared_ptr<Keyboard> keyboard;
    std::shared_ptr<Core> core;
    std::shared_ptr<Entity> entitySelf;
    std::shared_ptr<Camera> camera;

  };



}