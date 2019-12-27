#include <sr1/memory>

namespace olivera
{

class Texture;
class Shader;
class RenderTexture;

class Context
{
  static std::sr1::shared_ptr<Context> initialize();

  std::sr1::shared_ptr<Texture> createTexture();
  std::sr1::shared_ptr<Shader> createShader();
  std::sr1::shared_ptr<RenderTexture> createRenderTexture();

private:
  std::sr1::weak_ptr<Context> self;

};

}
