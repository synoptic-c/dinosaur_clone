#include"texture.hpp"
void Texture::LoadFromFile(const char* path)
{
	int width;
	int height;
	int channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	if (data)
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		int internalformat = 0;
		int format = 0;
		if (channels == 1)
		{
			internalformat = GL_R8;
			format = GL_RED;
		}
		if (channels == 2)
		{
			internalformat = GL_RG8;
			format = GL_RG;
		}
		if (channels == 3)
		{
			internalformat = GL_RGB8;
			format = GL_RGB;
		}
		if (channels == 4)
		{
			internalformat = GL_RGBA8;
			format = GL_RGBA;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else
	{
		std::cout << "Failed to load texture" << path << std::endl;
	}
	stbi_image_free(data);
}
void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
unsigned int Texture::GetTexture()
{
	return m_texture;
}
void Texture::Destroy()
{
	glDeleteTextures(1, &m_texture);
}
void TextureManager::LoadTextures(const std::vector<std::string>& paths)
{
	for (const std::string& path : paths)
	{
		m_textures.emplace_back();
		m_textures.back().LoadFromFile(path.c_str());
	}
}
void TextureManager::Bind(unsigned int index)
{
	m_textures[index].Bind();
}
void TextureManager::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
unsigned int TextureManager::GetSize()
{
	return m_textures.size();
}
void TextureManager::Destroy()
{
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		m_textures[i].Destroy();
	}
	m_textures.clear();
}