#include <olivera/olivera.h>
#include <memory>
#include <vector>


class  SoundInputManager : public olivera::Component
{

public:
  void onInitialise();

  void onTick();

  void playSound();


private:

  std::weak_ptr<olivera::Keyboard> keyboard;
  std::weak_ptr <olivera::Core> core;
  std::weak_ptr<olivera::Entity> entitySelf;
  std::shared_ptr<olivera::SoundSource> soundSource;

  std::vector <bool> Keys;
  



};



