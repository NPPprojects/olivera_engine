#include <olivera/olivera.h>
#include <memory>
#include <vector>
  class FPSCamera;


  class  CameraInputManager : public olivera::Component
  {

  public:
    void CameraMovement();

    void onInitialise();

    void onTick();

    void mouse_callback(double xpos, double ypos);

	void keysHeld();


 

  private:

    std::weak_ptr<olivera::Keyboard> keyboard;
    std::weak_ptr<olivera::Mouse> mouse;
    std::weak_ptr <olivera::Core> core;
    std::weak_ptr<olivera::Entity> entitySelf;
    std::weak_ptr<FPSCamera> camera;


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



