#include "scbpch.h"
#include "Scribble2D/Renderer/Texture.h"


namespace Scribble {

	Texture2D::Texture2D()
		: m_Width(0), m_Height(0), m_InternalFormat(GL_RGB), m_ImageFormat(GL_RGB), m_WrapS(GL_REPEAT), m_WrapT(GL_REPEAT), m_FilterMin(GL_LINEAR), m_FilterMax(GL_LINEAR)
	{
		glGenTextures(1, &m_TextureID);
	}

	void Texture2D::Generate(uint32_t width, uint32_t height, unsigned char* data)
	{
		m_Width = width;
		m_Height = height;

		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		
		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_ImageFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_WrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_FilterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_FilterMax);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}