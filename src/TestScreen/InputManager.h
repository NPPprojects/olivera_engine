#include <olivera/olivera.h>
#include <memory>
#include <vector>
  class FPSCamera;


  class  InputManager : public olivera::Component
  {

  public:
    void CameraMovement();

    void onInitialise();

    void onTick();

    void mouse_callback(double xpos, double ypos);

	void KeysHeld();
 

  private:

    std::shared_ptr<olivera::Keyboard> keyboard;
    std::shared_ptr<olivera::Mouse> mouse;
    std::shared_ptr <olivera::Core> core;
    std::shared_ptr<olivera::Entity> entitySelf;
    std::shared_ptr<FPSCamera> camera;

	std::vector <bool> Keys;
	struct KeyHeld 
	{
		bool w;
		bool a;
		bool s;
		bool d;

	};

    bool firstMouse;
    //Last Mouse location
    double lastX;
    double lastY;
	KeyHeld WASDPressed;
	KeyHeld WASDReleased;
  };



