#include <SDL2/SDL.h>

namespace olivera
{
/****************************************************
 @brief Class to keep track and record mouse events

*****************************************************/
  class Mouse 
  {
  public:

    /*******************************
    @brief Setter for isMouseMoving.

    ********************************/
      void setMouseState(bool _mouseMotion);
    /**************************************
    @brief Getter for X coordinate of the 
    mouse on the window.

    ***************************************/
      int getXCoordinate();

    /*******************************
    @brief Getter for isMouseMoving

    ********************************/
      bool getMouseState();

    /**************************************
    @brief Getter for Y coordinate of the
    mouse on the window.

    ***************************************/
      int getYCoordinate();

    /**************************************
    @brief Getter for mouses x coordinate
    relative motion

    @return X relative motion
    ***************************************/
      float getXMotion();

    /**************************************
    @brief Getter for mouses x coordinate
    relative motion

    @return Y relative motion
    ***************************************/
      float getYMotion();

    /**************************************
    @brief Setter for mouses x coordinate
    relative motion

    ***************************************/
      void setXMotion(int _xRelMotion);

    /**************************************
    @brief Setter for mouses x coordinate
    relative motion

    ***************************************/
      void setYMotion(int _yRelMotion);
                                                                  
    /**************************************************************
    @brief Set up mouse tracking every tick                       
                                                                  
    *Every tick, set the current mouse X and Y coordinates        
    based on where the mouse is on the window and set any relative
    X or Y motion event, when it's occuring.                      
                                                                  
    ***************************************************************/
      void tick(int _xRelMotion, int _yRelMotion);

  private:
  /*************************************************************************************************/
   
    int xCoord;                                                     //!<Mouse X Coordinates on window
    int yCoord;                                                     //!<Mouse Y Coordinates on window
                                                             
    float xMotion;                                                        //!<Mouse x relative motion
    float yMotion;                                                        //!<Mouse x relative motion

    bool isMouseMoving;               //Mouse boolean, event

  /*************************************************************************************************/
  };

}