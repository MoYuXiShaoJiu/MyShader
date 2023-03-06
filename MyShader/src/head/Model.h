#pragma once
#include"Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class MyModel
{
public:
	MyModel(const std::string path);
	~MyModel();
	void DrawModel(MyShader shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;
	//º¯Êý
	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		TexType  typeName);
	std::vector<Texture> textures_loaded;


};