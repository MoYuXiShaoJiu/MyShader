#include"Texture.h"
#include<iostream>
Texture::Texture(const std::string& path)
	:path(path)
{
	// Basic usage (see HDR discussion below for HDR usage):
	//    int x,y,n;
	//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
	//    // ... process data if not NULL ...
	//    // ... x = width, y = height, n = # 8-bit components per pixel ...
	//    // ... replace '0' with '1'..'4' to force that many components per pixel
	//    // ... but 'n' will always be the number that it would have been if you said 0
	//    stbi_image_free(data)
	//
	// Standard parameters:
	//    int *x                 -- outputs image width in pixels
	//    int *y                 -- outputs image height in pixels
	//    int *channels_in_file  -- outputs # of image components in image file
	//    int desired_channels   -- if non-zero, # of image components requested in result

	//x width,y height n
	int channels = 0;
	stbi_set_flip_vertically_on_load(1); 
	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &channels, 0);
	if (data)
	{
		if (channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}
		std::cout<< "format not supported"<<std::endl;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
		glTextureStorage2D(m_RenderID, 1, m_InternalFormat, m_width, m_height);

		glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RenderID, 0, 0, 0, m_width, m_height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);


	}
	else
	{
		std::cout<<"OpenGL Texture:stbi load texture fail!"<<std::endl;
	}

}

Texture::~Texture()
{
	glDeleteTextures(1, &this->m_RenderID);
}

void Texture::BindTexture(unsigned int num) const
{
	glBindTextureUnit(num, m_RenderID);
}

void Texture::UnBindTexture(unsigned int num) const
{
	glBindTextureUnit(0, m_RenderID);
}

int Texture::GetTextureWidth() const
{
	return m_width;
}

int Texture::GetTextureHeight() const
{
	return m_height;
}
