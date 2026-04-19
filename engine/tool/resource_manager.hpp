#pragma once
#include"../renderer/mesh.hpp"
#include<glad/glad.h>
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
namespace resourcemanager
{
	void LoadShaderSource(const char* path, std::string& shaderSource);
	std::vector<std::string> LoadFromList(const std::string& path);
	std::map<std::string, std::string> LoadFromIni(const std::string& path);
	void SaveToIni(const std::string& path, const std::map<std::string, std::string>& data);
	void LoadMesh(const MeshPath& meshPath, MeshData& meshData);
}