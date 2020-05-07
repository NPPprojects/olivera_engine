#include "Component.h"

namespace olivera
{
/*************************************
 @brief Calcuate and store delta time.

**************************************/
  class Environment 
  {
    public:
    
      /****************************
      @brief Getter for DeltaTime

      @return DeltaTime as a float
      *****************************/
      float getDeltaTime();

      /**********************************************
      @brief Initialise lastTime to SDL's tick rate 
      and sets the ideal framerate.

      ***********************************************/
        void initialise();

      /***********************************
      @brief sets deltaTime every tick 
    
      ************************************/
        void tick();

    private:
    /************************************************************************************************************/

      float deltaTime;                //!<Time value that would be equal to make movement the same on any system
      float lastTime;                 //!<Initially set to the amount of milisecond's since SDL's initialisation
      float idealTime;                                                 //!<Ideal frame rate set on initilisation

    /************************************************************************************************************/
  };

}