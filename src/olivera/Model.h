
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
  
  



  /****************************************************
  @brief Resource derived class for loading 3D models
  
  *****************************************************/
  class Model : public Resource
  {
    public:

      /****************************************************
      @brief Constructor, expects a filepath to a 3D model.
    
      @param std::string const @path to file
      @param bool gamma false by default

      *****************************************************/
      Model(std::string const &path, bool textureFlip = false, bool gamma = false);

      /*****************************************************************************
      @brief Draws the model and all its meshes using the specified shader program

      @param std::shared_ptr<ShaderProgram> shader file used by the model
      ******************************************************************************/
        void draw(std::shared_ptr<ShaderProgram> shader, unsigned int _shaderCubemap);

        void draw();



    


    private:
    /****************************************************************************************************************************************************************************/

        /***********************************************
         @brief Load texture from file path

         @param const char *path to file
         @param cosnt std::string& directory
         @param bool gamma false by default

         @return textureID
         ************************************************/
      unsigned int textureFromFile(const char *path, const std::string &directory);

      /*******************************************************************************
      @brief processes a node in a recursive fashion. Processes each individual mesh 
      located at the node and repeats this process on its children nodes (if any).
    
      ********************************************************************************/
        void processNode(aiNode *_node, const aiScene *_scene);

      /*******************************************************************************
      @brief processes a node in a recursive fashion. Processes each individual mesh
      located at the node and repeats this process on its children nodes (if any).

      ********************************************************************************/
        Mesh processMesh(aiMesh *_mesh, const aiScene *_scene);


      /*************************************************************
      @brief Checks all material textures of a given type and loads
      the textures if they're not loaded yet.
    
      @return Texture struct.

      **************************************************************/
       std::vector<Textures> loadMaterialTextures(aiMaterial *_mat, aiTextureType _type, std::string _typeName);

      /***************************************
      @brief Loads the model

      @param std::string const *Path to model
      ****************************************/
        void loadModel(std::string const &_path);


      /*  Model Data */

      std::vector<Textures> textures_loaded;                            //!<Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once
      std::vector<Mesh> meshes;                                                                                            //!<Stores all the meshes of the object that are loaded
      std::string directory;                                                                                                                     //!< Holds neccessary directories
      bool gammaCorrection;                                                                                                   //!<Gamma correct objects if specified in the object

      bool textureFlip;                                                                                         //!<Specify if the object's textures need to be vertically flipped

      /****************************************************************************************************************************************************************************/
  };
}

