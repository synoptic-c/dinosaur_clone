#pragma once
#include"../../engine/tool/resource_manager.hpp"
#include"../../engine/renderer/mesh.hpp"
#include"../../engine/renderer/shader.hpp"
#include"../../engine/renderer/texture.hpp"
#include"../../engine/math/transform.hpp"
#include"../../engine/collision/collision_data.hpp"
#include"../../engine/collision/collision_manager.hpp"
#include<glm/glm.hpp>
#include<cmath>
#include<vector>
#include<string>
#include<map>
struct GroundData
{
	glm::vec2 size;
	std::vector<glm::vec2> positions;
	std::vector<glm::vec2> setUpPositions;
	std::vector<size_t> styleIndices;
	CollisionBox collisionBox;
	float spacing;
};
class Ground
{
private:
	Mesh m_mesh;
	Shader m_shader;
	Texture m_texture;
	GroundData m_groundData;
public:
	void SetUp();
	void Create(const std::string& loadPath);
	GroundData& GetData();
	const std::vector<size_t>& GetStyleIndices();
	const std::vector<glm::vec2>& GetPositions();
	const CollisionBox& GetCollisionBox();
	void Update(const glm::vec2& camera);
	void Render(const glm::mat4& projection, const glm::vec2& camera);
	void Destroy();
};