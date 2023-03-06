#pragma once

#include<glm/glm.hpp>
#include<string>
#include<vector>
#include"shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
struct Vertex
{
	//一个顶点至少包含位置、法向量、纹理坐标
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;

};

enum class TexType
{
	None = 0,
	diffuse,
	spec
};
struct Texture
{
	//一个网格还应该包含用于索引绘制的索引以及纹理形式的材质数据（漫反射 / 镜面光贴图）
	unsigned int id;
	TexType type;
	aiString path;
	//纹理的id以及它的类型
};


class Mesh
{
	//一个网格至少有一系列顶点
public:
	Mesh(const std::vector<Vertex>& vertex, const std::vector<unsigned int >& index, const std::vector<Texture>& tex);
	~Mesh();
	void Draw(MyShader& shader);

	//get
	inline std::vector<Vertex>& GetVertices()  { return vertices; };
	inline std::vector<unsigned int>& GetIndices() { return indices; };
	inline std::vector<Texture>& GetTextures() { return textures; };
	//set
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int vao, vbo, ebo;
	void setupMesh();//在这里初始化缓冲
};


class Model
{

	

};
