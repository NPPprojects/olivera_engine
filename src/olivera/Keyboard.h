#include <SDL2/SDL.h>

#include <vector>
#include <memory>
namespace olivera 
{
  /**
* Class to process Keyboard inputs
*/
  class Keyboard 
  {
   
  public:

    
    /**
     * \Brief whenever a key gets pressed it gets added to the pressed keys vector
     */
    bool isKeyPressed(int key);

    /**
    * \Brief whenever a key gets released it gets added to the released keys vector
    */
    bool isKeyReleased(int key);

    /**
    * \Brief clears the keyPressed and KeyReleased vectors
    */
    void clearKey();

    /**
    * \Brief sets the keyboard state so that key presses can be tracked from inside core
    */
    void SetKeyboardState();

    /**
    * \Getter function for pressedKeys
    */
   std::vector<int> getKeyPressed();

   /**
    * \Getter function for releasedKeys
    */
	 std::vector<int> getKeyReleased();

  private:
    
    const Uint8 *keyboard_state_array;///<Set KeyboardState to track keyboard events.

	  bool released;///<Boolean to keep track of whenever keys get released

    std::vector<int> releasedKeys;///< Vector to store released keys
    
    std::vector<int> pressedKeys;///<Vector to store pressed keys


  
  };
  

}