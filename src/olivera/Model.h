
#include <GL/glew.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Mesh.h";
#include "Resource.h"
namespace olivera {


  class ShaderProgram;
  
  
  /**
  * Loads textures from files
  */
  unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);


  class Model : public Resource
  {
  public:

    /**
    *\ constructor, expects a filepath to a 3D model.
    */
    Model(std::string const &path, bool gamma = false);

    /**
    *\ draws the model and all its meshes
    */
    void draw(std::shared_ptr<ShaderProgram> shader);



  private:
  /**
  *\ loads the model and expects path to an .obj file
  */
    void loadModel(std::string const &_path);


    /**
    *\ processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    */
    void processNode(aiNode *_node, const aiScene *_scene);

    /**
    *\ processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    */
    Mesh processMesh(aiMesh *_mesh, const aiScene *_scene);



    /**
    \ checks all material textures of a given type and loads the textures if they're not loaded yet.
    \ the required info is returned as a Texture struct.
    */
    std::vector<Textures> loadMaterialTextures(aiMaterial *_mat, aiTextureType _type, std::string _typeName);
    /*  Model Data */

    std::vector<Textures> textures_loaded;///<stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;///<stores all the meshes of the object that are loaded
    std::string directory;///< holds neccessary directories
    bool gammaCorrection;///<gamma correct objects if specified in the object


  };
}

