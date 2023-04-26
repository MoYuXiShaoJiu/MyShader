#pragma once
#include<string>
#include<vector>
#include"stb_image.h"
#include<glad/glad.h>
class MyTexture
{
public:
	MyTexture(const std::string& path);
	~MyTexture();
	void BindTexture(unsigned int num = 0) const;
	void UnBindTexture(unsigned int num = 0)const;

	int GetTextureWidth()const;
	int GetTextureHeight()const;
private:
	int  m_width, m_height;
	int TextureID;
	GLenum m_InternalFormat = 0, m_DataFormat = 0;
	std::string path;
	GLuint m_RenderID;

};

class CubeTexture
{
public:
	CubeTexture(const std::vector<std::string>& path);
	~CubeTexture();
	void BindTexture(unsigned int num = 0) const;
	void UnBindTexture(unsigned int num = 0) const;
	int GetTextureID();

private:
	std::vector<std::string> path;
	GLuint m_TextureID;
};


