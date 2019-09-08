#pragma once
#include <assimp/scene.h>
#include <string>
#include <vector>

#include <LOGL/Mesh.h>
#include <LOGL/Shader.h>
namespace LOGL {

class Model {
   public:
    Model(char* path) { loadModel(path); }
    void Draw(Shader shader);

   private:
    /*  模型数据  */
    std::vector<Mesh> meshes;
    std::string directory;
    /*  函数   */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat,
                                              aiTextureType type,
                                              std::string typeName);
    std::vector<Texture> textures_loaded;
};
}  // namespace LOGL
