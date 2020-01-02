#include <SDL2/SDL.h>

#include <vector>
#include <memory>
namespace olivera 
{

  class Keyboard 
  {
   
  public:

    //void inputDetection(SDL_KeyboardEvent event);
    bool isKey(int key);
    void isKeyPressed(int key);
    void isKeyReleased(int key);
    void clearKey();

  
    std::vector<int> getKeyPressed();
  private:
  
    std::vector<int> keys;
    std::vector<int> releasedKeys;
    std::vector<int> pressedKeys;


  
  };
  

}