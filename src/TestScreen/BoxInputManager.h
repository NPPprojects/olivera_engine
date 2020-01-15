#include <olivera/olivera.h>
#include <memory>
#include <vector>



class  BoxInputManager : public olivera::Component
{

public:
  void BoxMovement();

  void onInitialise();

  void onTick();

  void keysHeld();




private:

  std::weak_ptr<olivera::Keyboard> keyboard;
  std::weak_ptr <olivera::Core> core;
  std::weak_ptr<olivera::Entity> entitySelf;

  std::vector <bool> Keys;
  struct KeyHeld
  {
    bool up;
    bool down;
    bool left;
    bool right;

  };

  //Last Mouse location

  KeyHeld UDLRPressed;
  KeyHeld UDLRReleased;
};



