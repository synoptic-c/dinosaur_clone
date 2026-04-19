#pragma once
#include<glad/glad.h>
#include<vector>
#include<string>
struct MeshPath
{
	std::string vertex;
	std::string index;
};
struct MeshData
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
};
class Mesh
{
private:
	unsigned int m_vertexArray;
	unsigned int m_vertexBuffer;
	unsigned int m_elementBuffer;
	unsigned int m_indexCount;
public:
	void LoadFromData(const MeshData& meshData);
	void Draw();
	void Destroy();
};