#include "Component.h"

namespace olivera
{
/**
* Class to calculate delta Time and set the framerate of the engine
*/
  class Environment 
  {
  public:
    /**
    * \ Getter for DeltaTime
    */
    float getDeltaTime();

    /**
    * \Brief inialise lastTime to SDL's tick rate and sets the ideal framerate
    */
    void initialise();

    /**
    * /Brief sets deltaTime every tick 
    */
    void tick();

  private:
    float deltaTime;///<Time value that would be equal to make movement the same on any system
    float lastTime;///<Last frame
    float idealTime;///<Ideal frame rate set on initilisation

  };

}