#pragma once
#include<glad/glad.h>
#include<stb_image.h>
#include<iostream>
#include<vector>
class Texture
{
private:
	unsigned int m_texture;
public:
	void LoadFromFile(const char* path);
	void Bind();
	void UnBind();
	unsigned int GetTexture();
	void Destroy();
};
class TextureManager
{
private:
	std::vector<Texture> m_textures;
public:
	void LoadTextures(const std::vector<std::string>& paths);
	void Bind(unsigned int index);
	void UnBind();
	unsigned int GetSize();
	void Destroy();
};