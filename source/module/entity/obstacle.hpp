#pragma once
#include"../../../engine/tool/resource_manager.hpp"
#include"../../../engine/renderer/mesh.hpp"
#include"../../../engine/renderer/shader.hpp"
#include"../../../engine/renderer/texture.hpp"
#include"../../../engine/math/transform.hpp"
#include"../../engine/collision/collision_data.hpp"
#include"../../engine/collision/collision_manager.hpp"
#include<glm/glm.hpp>
#include<random>
#include<vector>
#include<string>
#include<map>
struct ObstacleData
{
	size_t instanceCount;
	float minRespawnOffset;
	float maxRespawnOffset;
	float positionY;
	float safetyValue;
	float generateDistance;
	float spacing;
	std::vector<glm::vec2> positions;
	std::vector<size_t> indices;
	std::vector<glm::vec2> sizes;
	std::vector<size_t> textureIndices;
	std::vector<CollisionBox> collisionBoxes;
};
class Obstacle
{
private:
	Mesh m_mesh;
	Shader m_shader;
	TextureManager m_textureManager;
	ObstacleData m_obstacleData;
	std::random_device m_randomDevice;
	std::mt19937 m_rng{ m_randomDevice() };
public:
	void SetUp(const glm::vec2& projection);
	void Create(const std::string& loadPath);
	ObstacleData& GetData();
	const std::vector<glm::vec2>& GetPositions();
	const std::vector<size_t>& GetIndices();
	const std::vector<CollisionBox>& GetCollisionBoxes();
	void Update(const glm::vec2& projection, const glm::vec2& camera);
	void Render(const glm::mat4& projection, const glm::vec2& camera);
	void Destroy();
};