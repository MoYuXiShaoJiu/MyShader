#pragma once
#include<string>
#include"stb_image.h"
#include<glad/glad.h>
class Texture
{
public:
	Texture(const std::string& path);
	~Texture();
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




