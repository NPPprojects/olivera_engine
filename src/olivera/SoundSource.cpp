#include "SoundSource.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "CurrentCamera.h"

#include "Sound.h"
#include "ResourceManager.h"
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
    alListener3f(AL_POSITION, 
      cameraTransform.lock()->getPosition().x,
      cameraTransform.lock()->getPosition().y,
      cameraTransform.lock()->getPosition().z);
    alSource3f(sid, AL_POSITION, 
      selfTransform.lock()->getPosition().x,
      selfTransform.lock()->getPosition().y,
      selfTransform.lock()->getPosition().z);
    alSourcei(sid, AL_BUFFER, sound.lock()->getId());
    alSourcePlay(sid);

  }
  void SoundSource::setIsPlaying(bool _val)
  {
     isPlaying = _val;
  }
}