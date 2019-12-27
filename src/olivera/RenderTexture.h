#include "mathutil.h"
#include "TextureAdapter.h"

#include <GL/glew.h>

#include <sr1/memory>
#include <sr1/noncopyable>
#include <sr1/zero_initialized>
#include <sr1/vector>

namespace olivera
{

class Context;
class Shader;

class RenderTexture : public TextureAdapter, public std::sr1::noncopyable
{
public:
  ~RenderTexture();

  void setSize(unsigned int width, unsigned int height);

  ivec2 getSize() const;
  int getWidth() const;
  int getHeight() const;

  GLuint getTexId();
  GLuint getId();
  void clear();

private:
  friend class Context;
  friend class Shader;

  std::sr1::shared_ptr<Context> context;
  std::sr1::zero_initialized<GLuint> fboId;
  std::sr1::zero_initialized<GLuint> rboId;
  std::sr1::zero_initialized<GLuint> id;
  ivec2 size;
  std::sr1::zero_initialized<bool> dirty;

};

}
