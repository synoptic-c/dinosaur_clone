#include"resource_manager.hpp"
void resourcemanager::LoadShaderSource(const char* path, std::string& shaderSource)
{
	std::fstream file(path);
	if (!file)
	{
		std::cout << "Failed to open file" << path << std::endl;
		file.close();
		return;
	}
	std::stringstream source;
	source << file.rdbuf();
	shaderSource = source.str();
	size_t start = shaderSource.find("#version");
	if (start == std::string::npos)
	{
		std::cout << "No #version directive found" << std::endl;
		return;
	}
	size_t end = shaderSource.find("\n", start);
	if (end == std::string::npos)
	{
		end = shaderSource.length();
	}
	int major = 3;
	int minor = 3;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	int glslVersion = major * 100 + minor * 10;
	shaderSource.replace(start, end - start, "#version " + std::to_string(glslVersion) + " core");
	file.close();
}
std::vector<std::string> resourcemanager::LoadFromList(const std::string& path)
{
	std::fstream file(path);
	std::vector<std::string> paths;
	if (!file)
	{
		std::cout << "Failed to open file" << path << std::endl;
		file.close();
		return paths;
	}
	std::string line;
	while (std::getline(file, line))
	{
		line.erase(0, line.find_first_not_of(" \r\t\n"));
		line.erase(line.find_last_not_of(" \r\t\n") + 1);
		if (!line.empty())
		{
			paths.push_back(line);
		}
	}
	file.close();
	return paths;
}
std::map<std::string, std::string> resourcemanager::LoadFromIni(const std::string& path)
{
	std::fstream file(path);
	std::map<std::string, std::string> data;
	if (!file)
	{
		std::cout << "Failed to open file" << path << std::endl;
		file.close();
		return data;
	}
	std::string line;
	while (std::getline(file, line))
	{
		line.erase(0, line.find_first_not_of(" \r\t\n"));
		line.erase(line.find_last_not_of(" \r\t\n") + 1);
		if (line.empty())
		{
			continue;
		}
		size_t position = line.find("=");
		if (position != std::string::npos)
		{
			std::string key = line.substr(0, position);
			std::string value = line.substr(position + 1);
			key.erase(0, key.find_first_not_of(" \r\t\n"));
			key.erase(key.find_last_not_of(" \r\t\n") + 1);
			value.erase(0, value.find_first_not_of(" \r\t\n"));
			value.erase(value.find_last_not_of(" \r\t\n") + 1);
			data.emplace(key, value);
		}
	}
	file.close();
	return data;
}
void resourcemanager::SaveToIni(const std::string& path, const std::map<std::string, std::string>& data)
{
	std::ofstream file(path);
	if (!file)
	{
		std::cout << "Failed to create/open file" << path << std::endl;
		file.close();
		return;
	}
	for (const auto& [key, value] : data)
	{
		file << key << "=" << value << std::endl;
	}
	file.close();
}
void resourcemanager::LoadMesh(const MeshPath& meshPath, MeshData& meshData)
{
	std::fstream file(meshPath.vertex);
	std::string line;
	if (!file)
	{
		std::cout << "Failed to open vertex file" << meshPath.vertex << std::endl;
		return;
	}
	while (std::getline(file, line))
	{
		float x, y, u, v;
		if (sscanf(line.c_str(), "%f %f %f %f", &x, &y, &u, &v) > 0)
		{
			meshData.vertices.push_back(x);
			meshData.vertices.push_back(y);
			meshData.vertices.push_back(u);
			meshData.vertices.push_back(v);
		}
	}
	file.close();
	file.open(meshPath.index);
	if (!file)
	{
		std::cout << "Failed to open index file" << meshPath.index << std::endl;
		return;
	}
	while (std::getline(file, line))
	{
		unsigned int v0, v1, v2;
		if (sscanf(line.c_str(), "%u %u %u", &v0, &v1, &v2) > 0)
		{
			meshData.indices.push_back(v0);
			meshData.indices.push_back(v1);
			meshData.indices.push_back(v2);
		}
	}
	file.close();
}