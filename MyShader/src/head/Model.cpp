#include"Model.h"
#include<iostream>
MyModel::MyModel(const std::string path)
{
	LoadModel(path);
}

MyModel::~MyModel()
{
}

void MyModel::DrawModel(MyShader shader)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void MyModel::LoadModel(std::string path)
{
	Assimp::Importer Myimport;
	const aiScene* scene = Myimport.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)//��鳡���͸��ڵ㲻Ϊnull
	{
		std::cout << "Error Assimp:" << Myimport.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void MyModel::ProcessNode(aiNode* node, const aiScene* scene)//�ݹ�Ĵ���node
{
	// ����ڵ����е���������еĻ���
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	// �������������ӽڵ��ظ���һ����
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh MyModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> MyModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	return std::vector<Texture>();
}
