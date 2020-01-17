#include "Component.h"

#include <string>
#include <memory>

namespace olivera
{

  class Sound;
  class Transform;

  /**
  *Componenet derived class that holds a sound and plays it to a listener entity
  */
  class SoundSource : public Component
  {
  public:
    /**
    *\ Initalise soundSource class
    */
    void onInitialise(std::string _name, std::shared_ptr<Entity> _cameraEntity);
    
    /**
    *\ update the locations of the sound source entity and the listener entity and check if the sound is playing every tick
    */
    void onTick();
    
    /**
    *\ when play is called the sound attached to the SoundCource component will play
    */
    void play();

    /**
    *\ Setter for IsPlaying
    */
    void SetIsPlaying(bool _val);

  private:
    std::weak_ptr<Sound> sound;///< Weak pointer to the sound file
 
    std::weak_ptr<Entity> entitySelf;///< weak pointer to self entity

    std::weak_ptr<Core> core;///< weak pointer to the core

    std::weak_ptr<Entity> cameraEntity;///< weak pointer to the camera Entity which is the listener 

    std::weak_ptr<Transform> selfTransform;///< Transform for the entity with the sound source component attached

    std::weak_ptr<Transform> cameraTransform;///< Transform for the camera Entity which is the listener 

    bool isPlaying;
  };

}