#include <memory>
#include <string>

namespace olivera
{

struct SoundImpl;

class Sound
{
  std::shared_ptr<SoundImpl> impl;

public:
  Sound();
  Sound(std::string path);
  void load(std::string path);
  void play(float vol, float varMin, float varMax);
  void play();

};

}
