#include "Component.h"

#include <string>
#include <memory>

/****************************************************************************
REWORK CLASS NEED TO IMPLEMENT ATTENUATION
*****************************************************************************/


namespace olivera
{

  class Sound;
  class Transform;

  /************************************************************************************
  @brief Componenet derived class that holds a sound and plays it to a listener entity

  *************************************************************************************/
  class SoundSource : public Component
  {
    public:

      /***********************************
      @brief Initalise soundSource class
    
      ************************************/
        void onInitialise(std::string _name, std::shared_ptr<Entity> _cameraEntity);
    
      /**************************************************************************
      @brief update the locations of the sound source entity and the listener 
      entity and check if the sound is playing every tick

      ***************************************************************************/
        void onTick();
    
      /*****************************************************************
      @brief When called the sound attached to the component will play

      ******************************************************************/
      void play();

      /****************************
      @brief Setter for IsPlaying

      *****************************/
      void setIsPlaying(bool _val);

    private:
    /*******************************************************************************************************************************/

      std::weak_ptr<Sound> sound;                                                                //!< Weak pointer to the sound file
      std::weak_ptr<Entity> entitySelf;                                                             //!< eak pointer to self entity
      std::weak_ptr<Core> core;                                                                        //!< Weak pointer to the core
      std::weak_ptr<Entity> cameraEntity;                               //!< Weak pointer to the camera Entity which is the listener 
      std::weak_ptr<Transform> selfTransform;                 //!< Transform for the entity with the sound source component attached
      std::weak_ptr<Transform> cameraTransform;                           //!< Transform for the camera Entity which is the listener 

      bool isPlaying;                                                     //!< Boolean used to enable and disable the attached sound

    /*******************************************************************************************************************************/
  };

}