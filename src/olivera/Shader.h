#include "mathutil.h"

#include <GL/glew.h>

#include <sr1/zero_initialized>
#include <sr1/noncopyable>
#include <sr1/memory>
#include <sr1/vector>

#include <string>

namespace olivera
{

  class Context;
  class VariableInfo;
  class Buffer;
  class RenderTexture;
  class TextureAdapter;

class Shader : public std::sr1::noncopyable
{
public:
  ~Shader();

  void render();
  void render(const std::sr1::shared_ptr<RenderTexture>& target);

  GLuint getId();
  void setSource(const std::string& source);

  void setUniform(const std::string& variable, float value);
  void setUniform(const std::string& variable, mat4 value);
  void setUniform(const std::string& variable, vec2 value);
  void setUniform(const std::string& variable, vec3 value);
  void setUniform(const std::string& variable, vec4 value);
  void setAttribute(const std::string& variable, const std::sr1::shared_ptr<Buffer>& value);
  void setSampler(const std::string& variable, const std::sr1::shared_ptr<TextureAdapter>& value);

private:
  friend class Context;

  std::sr1::shared_ptr<Context> context;
  std::sr1::zero_initialized<GLuint> id;
  std::sr1::vector<std::sr1::shared_ptr<VariableInfo> > cache;

  std::sr1::shared_ptr<VariableInfo> getVariableInfo(const std::string& name, GLenum type, bool attrib);

};

}
