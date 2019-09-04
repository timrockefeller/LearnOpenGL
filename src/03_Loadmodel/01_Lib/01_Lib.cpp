#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <iostream>
using namespace std;

int main(int argc, char const* argv[]) {
    cout << "Running";
    Assimp::Importer importer;
    const aiScene* scene =
        importer.ReadFile("", aiProcess_Triangulate | aiProcess_FlipUVs);
    cout << scene;
    return 0;
}
