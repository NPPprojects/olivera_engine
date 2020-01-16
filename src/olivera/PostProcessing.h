#include <memory>


namespace olivera
{
  
  class Core;

  class ShaderProgram;
 
  class VertexBuffer;

  class PostProcessing
  {
  public:

    PostProcessing(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh);

    ~PostProcessing();

    void FrameBufferConfiguration();

    int getFBO();
    void use();

  private:

    unsigned int FBO;
    unsigned int textureColorBuffer;
    unsigned int renderBuffer;


    int blurIntesity;
    float exposure;
    float gamma;
    bool filter;

    std::shared_ptr<VertexBuffer> squareMesh;
    std::shared_ptr<ShaderProgram> shader;
    std::weak_ptr<Core> core;
  };


}