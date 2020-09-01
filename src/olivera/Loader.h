#include <memory>

namespace olivera
{

  class ShaderProgram;
  class VertexArray;
  class Texture;
  


  class Loader
  {
    public:
      Loader(std::shared_ptr<Texture> _texture);


    private:

      std::shared_ptr<Texture> texture;
      std::shared_ptr<VertexArray> mesh;
      std::shared_ptr<ShaderProgram> shader;
  };


}