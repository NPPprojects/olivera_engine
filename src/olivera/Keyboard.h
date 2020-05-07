#include <SDL2/SDL.h>

#include <vector>
#include <memory>

/********************************************************************
SetKeyboardState might be useless
*********************************************************************/

namespace olivera 
{
  /*******************************
  @brief Process keyboard inputs.

  *Provides methods to access 
  released and pressed key.

  ********************************/
  class Keyboard 
  {  
    public:

      /************************************************************************
      @brief When a key gets pressed it gets added to the pressed keys list.
    
      @param int key code of the currently pressed key

      @return released bollean set to false

      ************************************************************************/
        bool isKeyPressed(int _key);

      /************************************************************************
      @brief When a key gets released it gets added to the released keys list.

      @param int key code of the currently released key

      @return released bollean set to true

      ************************************************************************/
        bool isKeyReleased(int _key);

      /*****************************************************
      @brief Clears the keyPressed and KeyReleased vectors.

      ******************************************************/
        void clearKey();

      /******************************************
      @brief Sets the keyboard state so that key 
      presses can be tracked from inside core.
      *******************************************/
        void SetKeyboardState();

      /**************************************
      @brief Getter function for pressedKeys.
    
      @return vector of pressed keys.
      ***************************************/
        std::vector<int> getKeyPressed();

     /***************************************
     @brief Getter function for releasedKeys.

     @return vector of released keys.
     ****************************************/
	      std::vector<int> getKeyReleased();

    private:
    /***************************************************************************************************************/

      const Uint8 *keyboard_state_array;                             //!< Set KeyboardState to track keyboard events

	    bool released;                                        //!< Boolean to keep track of whenever keys get released

      std::vector<int> releasedKeys;                                              //!< Vector to store released keys  
      std::vector<int> pressedKeys;                                                //!< Vector to store pressed keys

    /***************************************************************************************************************/
  };
  

}