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
	//һ���������ٰ���λ�á�����������������
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
	//һ������Ӧ�ð��������������Ƶ������Լ�������ʽ�Ĳ������ݣ������� / �������ͼ��
	unsigned int id;
	TexType type;
	aiString path;
	//�����id�Լ���������
};


class Mesh
{
	//һ������������һϵ�ж���
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
	void setupMesh();//�������ʼ������
};


class Model
{

	

};
