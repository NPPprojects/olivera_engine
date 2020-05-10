#include "SoundSource.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "CurrentCamera.h"

#include "Sound.h"
#include "ResourceManager.h"

#include <iostream>
namespace olivera
{
  void SoundSource::onInitialise(std::string _name, std::shared_ptr<Entity> _cameraEntity)
  {
    isPlaying = false;
    entitySelf = getEntity();
    core = getCore();
    sound = core.lock()->getResources()->load<Sound>(_name);

    cameraEntity = _cameraEntity;
  }



  void SoundSource::onTick()
  {
    selfTransform = entitySelf.lock()->getComponent<Transform>();
    cameraTransform = cameraEntity.lock()->getComponent<Transform>();
    if (isPlaying == true)
    {
      play();
      isPlaying = false;
    }
  }

  void SoundSource::play()
  {
    ALuint sid = 0;
    alGenSources(1, &sid);
    alSource3f(sid, AL_POSITION,
      selfTransform.lock()->getPosition().x,
      selfTransform.lock()->getPosition().y,
      selfTransform.lock()->getPosition().z);

    alListener3f(AL_POSITION, 
      cameraTransform.lock()->getPosition().x,
      cameraTransform.lock()->getPosition().y,
      cameraTransform.lock()->getPosition().z);
    
    orientation[0] = cameraTransform.lock()->getFront().x;
    orientation[1] = cameraTransform.lock()->getFront().y;
    orientation[2] = cameraTransform.lock()->getFront().z;

    orientation[3] = cameraTransform.lock()->getWorldUp().x;
    orientation[4] = cameraTransform.lock()->getWorldUp().y;
    orientation[5] = cameraTransform.lock()->getWorldUp().z;

    alListenerfv(AL_ORIENTATION,orientation);
    std::cout << cameraTransform.lock()->getPosition().x << "  " << cameraTransform.lock()->getPosition().y << "  " << cameraTransform.lock()->getPosition().z << std::endl;
    alSourcei(sid, AL_BUFFER, sound.lock()->getId());
    alSourcePlay(sid);

  }
  void SoundSource::setIsPlaying(bool _val)
  {
     isPlaying = _val;
  }
}