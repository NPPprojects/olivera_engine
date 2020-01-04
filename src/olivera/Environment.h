#include "Component.h"

namespace olivera
{
  class Environment 
  {
  public:
    float getDeltaTime();

    void initialise();

    void tick();

  private:
    float deltaTime; //Time value that would be equal to make movement the same on any system
    float lastTime;  //last frame
    float idealTime; // Ideal frame rate set on initilisation

  };

}