#include "Model.h"

namespace olivera
{


  // constructor, expects a filepath to a 3D model.
  Model::Model(std::string const &_path, bool _gamma) : gammaCorrection(_gamma)
  {
    loadModel(_path);
  }

  // draws the model, and thus all its meshes
  void Model::draw(std::shared_ptr<ShaderProgram> _shader, unsigned int _shaderCubemap)
  {
    for (unsigned int i = 0; i < meshes.size(); i++)
      meshes[i].draw(_shader,  _shaderCubemap);
  }

  void Model::draw()
  {
    for (unsigned int i = 0; i < meshes.size(); i++)
      meshes[i].draw();
  }



  /*  Functions   */
  // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
  void Model::loadModel(std::string const &_path)
  {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
      std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
      return;
    }
    // retrieve the directory path of the filepath
    directory = _path.substr(0, _path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
  }

  // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
  void Model::processNode(aiNode *_node, const aiScene *_scene)
  {
    // process each mesh located at the current node
    for (unsigned int i = 0; i < _node->mNumMeshes; i++)
    {
      // the node object only contains indices to index the actual objects in the scene. 
      // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
      aiMesh* mesh = _scene->mMeshes[_node->mMeshes[i]];
      meshes.push_back(processMesh(mesh, _scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < _node->mNumChildren; i++)
    {
      processNode(_node->mChildren[i], _scene);
    }

  }

  Mesh Model::processMesh(aiMesh *_mesh, const aiScene *_scene)
  {
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Textures> textures;

    // Walk through each of the mesh's vertices
    for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
    {
      Vertex vertex;
      glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
      // positions
      vector.x = _mesh->mVertices[i].x;
      vector.y = _mesh->mVertices[i].y;
      vector.z = _mesh->mVertices[i].z;
      vertex.Position = vector;
      // normals
      vector.x = _mesh->mNormals[i].x;
      vector.y = _mesh->mNormals[i].y;
      vector.z = _mesh->mNormals[i].z;
      vertex.Normal = vector;
      // texture coordinates
      if (_mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
      {
        glm::vec2 vec;
        // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
        // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
        vec.x = _mesh->mTextureCoords[0][i].x;
        vec.y = _mesh->mTextureCoords[0][i].y;
        vertex.TexCoords = vec;
      }
      else
        vertex.TexCoords = glm::vec2(0.0f, 0.0f);
      // tangent
      vector.x = _mesh->mTangents[i].x;
      vector.y = _mesh->mTangents[i].y;
      vector.z = _mesh->mTangents[i].z;
      vertex.Tangent = vector;
      // bitangent
      vector.x = _mesh->mBitangents[i].x;
      vector.y = _mesh->mBitangents[i].y;
      vector.z = _mesh->mBitangents[i].z;
      vertex.Bitangent = vector;
      vertices.push_back(vertex);
    }
    // now wak through each of the _mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
    {
      aiFace face = _mesh->mFaces[i];
      // retrieve all indices of the face and store them in the indices vector
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Textures> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Textures> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Textures> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Textures> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
  }

  // checks all material textures of a given type and loads the textures if they're not loaded yet.
  // the required info is returned as a Texture struct.
  std::vector<Textures> Model::loadMaterialTextures(aiMaterial *_mat, aiTextureType _type, std::string _typeName)
  {
    std::vector<Textures> textures;
    for (unsigned int i = 0; i < _mat->GetTextureCount(_type); i++)
    {
      aiString str;
      _mat->GetTexture(_type, i, &str);
      // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
      bool skip = false;
      for (unsigned int j = 0; j < textures_loaded.size(); j++)
      {
        if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
        {
          textures.push_back(textures_loaded[j]);
          skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
          break;
        }
      }
      if (!skip)
      {   // if texture hasn't been loaded already, load it
        Textures texture;
        texture.id = textureFromFile(str.C_Str(), this->directory);
        texture.type = _typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
        textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
      }
    }
    return textures;
  }



  unsigned int textureFromFile(const char *_path, const std::string &_directory, bool _gamma)
  {
    std::string filename = std::string(_path);
    filename = _directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
      GLenum format;
      if (nrComponents == 1)
        format = GL_RED;
      else if (nrComponents == 3)
        format = GL_RGB;
      else if (nrComponents == 4)
        format = GL_RGBA;

      glBindTexture(GL_TEXTURE_2D, textureID);
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      stbi_image_free(data);
    }
    else
    {
      std::cout << "Texture failed to load at path: " << _path << std::endl;
      stbi_image_free(data);
    }

    return textureID;
  }

}