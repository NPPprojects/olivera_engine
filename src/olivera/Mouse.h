#include <SDL2/SDL.h>

namespace olivera
{
/**
* Class to keep track of Mouse state
*/
  class Mouse 
  {
  public:
    /**
* \ Setter for Mouse motion state
*/
      void setMouseState(bool _mouseMotion);
    /**
* \ Getter for XCoordinate on window
*/
    int getXCoordinate();

/**
* \ Getter to check if mouse is moving
*/
    bool getMouseState();

/**
* \ Getter for YCoodinate on window
*/
   int getYCoordinate();

   /**
* \ Getter for X relative motion
*/
   float getXMotion();

   /**
   * \ Getter for Y relative motion 
   */
   float getYMotion();

/**
* \ Getter for YCoodinate on window
*/
   void setXMotion(int _xRelMotion);
/**
* \ Getter for YCoodinate on window
*/
   void setYMotion(int _yRelMotion);

  /**
  * \ Update x and Y mouse Coordinate every tick
  */
   void tick(int _xRelMotion, int _yRelMotion);
  private:
    int xCoord;///<Mouse X Coordinates on window
    int yCoord;///<Mouse Y Coordinates on window

    float xMotion;///<Mouse x relative motion
    float yMotion;///<Mouse x relative motion

    bool isMouseMoving;
  };

}