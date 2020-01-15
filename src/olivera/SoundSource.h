#include "Component.h"

#include <string>
#include <memory>

namespace olivera
{

  class Sound;
  class Transform;

  class SoundSource : public Component
  {
  public:
    void onInitialise(std::string _name, std::shared_ptr<Entity> _cameraEntity);
    void onTick();
    void play();

    void SetIsPlaying(bool _val) { isPlaying = _val; }

  private:
    std::weak_ptr<Sound> sound;
 
    std::weak_ptr<Entity> entitySelf;
    std::weak_ptr<Core> core;
    std::weak_ptr<Entity> cameraEntity;
    std::weak_ptr<Transform> selfTransform;
    std::weak_ptr<Transform> cameraTransform;

    bool isPlaying = false;
  };

}