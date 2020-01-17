#include "SoundInputManager.h"

void SoundInputManager::onInitialise()
{
  core = getCore();

  std::cout << "Initialise Sound Input Manager Manager" << std::endl;

  entitySelf = getEntity();

  keyboard = core.lock()->getKeyboard();
  
  soundSource = entitySelf.lock()->getComponent<olivera::SoundSource>();
}

void SoundInputManager::onTick()
{
  playSound();
}

void SoundInputManager::playSound()
{
   if (keyboard.lock()->getKeyPressed().size() > 0)
  {
    if (keyboard.lock()->getKeyPressed().at(0) == SDL_SCANCODE_T)
    {
      soundSource->setIsPlaying(true);
      std::cout << "Sound Plays Yay" << std::endl;
    }
  }
}
