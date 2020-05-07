
#include "Resource.h"
#include <AL/al.h>
#include <vector>
namespace olivera
{
  /******************************************************
  @brief Resource derived class for playing audio files

  *******************************************************/
  class Sound : public Resource
  {
    public:
     
      /*******************************************
      @brief Constructor that calls load function.

      @param std::string path to file

      ********************************************/
        Sound(std::string _path);

      /*******&&*******************************
      @brief Destructor for the sound resource

      *****************************************/
        ~Sound() { alDeleteBuffers(1, &id); }

      /*******************************************************
      @brief Load an audio file from the specified file path.

      @param std::string _path 

      ********************************************************/
        void load(std::string _path);

      /*********************
      @brief Load .ogg file
     
      **********************/
        void loadOggFile(const std::string& fileName, std::vector<char>& buffer,
                         ALenum &format, ALsizei &freq);
      
      /********************
      @brief Getter for ID 
      *********************/
        ALuint getId();

    private:
    /*************************************************************************************************/
      
      ALuint id;                                                             //!< ID to refrence sound

    /*************************************************************************************************/
  };
}