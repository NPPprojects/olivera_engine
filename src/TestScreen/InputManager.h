#include <olivera/olivera.h>
#include <memory>

  class FPSCamera;


  class  InputManager : public olivera::Component
  {

  public:
    void CameraMovement();

    void onInitialise();

    void onTick();

    void mouse_callback(double xpos, double ypos);
 

  private:

    std::shared_ptr<olivera::Keyboard> keyboard;
    std::shared_ptr<olivera::Mouse> mouse;
    std::shared_ptr <olivera::Core> core;
    std::shared_ptr<olivera::Entity> entitySelf;
    std::shared_ptr<FPSCamera> camera;

    bool firstMouse;
    //Last Mouse location
    double lastX;
    double lastY;
  };



