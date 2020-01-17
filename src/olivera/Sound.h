
#include "Resource.h"
#include <AL/al.h>
#include <vector>
namespace olivera
{
  /**
  * Resource derived Class that holds a sound file
  */
  class Sound : public Resource
  {
  public:
   
    /**
    *\ Constructor that calls load function upon creation
    */
    Sound(std::string _path);

    /**
    *\ Destructor for the sound Resource
    */
    ~Sound() { alDeleteBuffers(1, &id); }

    /**
    *\ Generate sound from sound file location
    */
    void load(std::string _path);

    /**
    *\ Load .ogg file
    */
    void loadOggFile(const std::string& fileName, std::vector<char>& buffer,
      ALenum &format, ALsizei &freq);
    
    /**
    *\ Getter for ID 
    */
    ALuint getId() { return id; }

  private:
    ALuint id;///< ID to access sound after its created
  };
}