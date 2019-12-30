#include "Component.h"
#include <memory>
namespace olivera
{

  class Keyboard;
  class Core;

  class  InputManager : public Component
  {
  public:
    void CameraMovement();

    void onInitialise(std::shared_ptr<Core> _core);

    void onTick();
  private:

    std::shared_ptr<Keyboard> keyboard;
    std::shared_ptr<Core> core;


  };



}