namespace olivera
{
/**
* Class to keep track of Mouse state
*/
  class Mouse 
  {
  public:
  /**
  * \ Getter for XCoordinate on window
  */
  int getXCoordinate();

  /**
  * \ Getter for YCoodinate on window
  */
   int getYCoordinate();

  /**
  * \ Update x and Y mouse Coordinate every tick
  */
   void tick();
  private:
    int x;///<Mouse X Coordinates on window
    int y;///<Mouse Y Coordinates on window

  };

}