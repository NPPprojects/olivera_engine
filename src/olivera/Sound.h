
#include "Resource.h"
#include <AL/al.h>
#include <vector>
namespace olivera
{

  class Sound : public Resource
  {
  private:
    ALuint id;

  public:
    Sound() {};
    Sound(std::string _path);
    ~Sound() { alDeleteBuffers(1, &id); }

    void load(std::string _path);

    void loadOggFile(const std::string& fileName, std::vector<char>& buffer,
      ALenum &format, ALsizei &freq);

    ALuint getId() { return id; }
  };
}