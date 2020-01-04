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
    void SetKeyboardState();
  
    std::vector<int> getKeyPressed();
  private:
    
    const Uint8 *keyboard_state_array;  //Set KeyboardState to track keyboard events;


    std::vector<int> keys;
    std::vector<int> releasedKeys;
    std::vector<int> pressedKeys;


  
  };
  

}