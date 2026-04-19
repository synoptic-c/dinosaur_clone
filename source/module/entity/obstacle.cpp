#include"obstacle.hpp"
void Obstacle::SetUp(const glm::vec2& projection)
{
	m_obstacleData.positions.clear();
	m_obstacleData.indices.clear();
	for (size_t i = 0; i < m_obstacleData.instanceCount; i++)
	{
		m_obstacleData.indices.push_back(std::uniform_int_distribution<size_t>(0, m_obstacleData.textureIndices.size() > 0 ? m_obstacleData.textureIndices.size() - 1 : m_obstacleData.textureIndices.size())(m_rng));
		m_obstacleData.positions.push_back(glm::vec2(m_obstacleData.safetyValue + std::uniform_real_distribution<float>(m_obstacleData.minRespawnOffset, m_obstacleData.maxRespawnOffset)(m_rng) + m_obstacleData.sizes[m_obstacleData.indices[i]].x + (m_obstacleData.spacing * i), m_obstacleData.positionY));
	}
}
void Obstacle::Create(const std::string& loadPath)
{
	std::map<std::string, std::string> resourcesPath = resourcemanager::LoadFromIni(loadPath);
	MeshData meshData;
	resourcemanager::LoadMesh({ resourcesPath["ver_path"], resourcesPath["idx_path"] }, meshData);
	m_mesh.LoadFromData(meshData);
	m_shader.LoadFromFile({ resourcesPath["vertex_path"], resourcesPath["fragment_path"] });
	m_textureManager.LoadTextures(resourcemanager::LoadFromList(resourcesPath["textures_path"]));
	CollisionBox collisionBox = collisionmanager::LoadFromData(resourcesPath["collision_point_path"]);
	std::vector<std::string> loadStyles = resourcemanager::LoadFromList(resourcesPath["obstacle_styles_path"]);
	for (size_t i = 0; i + 2 < loadStyles.size(); i += 3)
	{
		glm::vec2 size = glm::vec2(std::stof(loadStyles[i]), std::stof(loadStyles[i + 1]));
		size_t textureIndex = std::stoul(loadStyles[i + 2]);
		CollisionBox loadCollisionBox = { collisionBox.left * size.x, collisionBox.right * size.x, collisionBox.up * size.y, collisionBox.down * size.y };
		m_obstacleData.sizes.push_back(size);
		m_obstacleData.textureIndices.push_back(textureIndex);
		m_obstacleData.collisionBoxes.push_back(loadCollisionBox);
	}
	std::map<std::string, std::string> loadData = resourcemanager::LoadFromIni(resourcesPath["data_path"]);
	m_obstacleData.instanceCount = std::stoul(loadData["instance_count"]);
	m_obstacleData.minRespawnOffset = std::stof(loadData["min_respawn_offset"]);
	m_obstacleData.maxRespawnOffset = std::stof(loadData["max_respawn_offset"]);
	m_obstacleData.positionY = std::stof(loadData["position_y"]);
	m_obstacleData.safetyValue = std::stof(loadData["safety_value"]);
	m_obstacleData.generateDistance = std::stof(loadData["generate_distance"]);
	m_obstacleData.spacing = std::stof(loadData["spacing"]);
}
ObstacleData& Obstacle::GetData()
{
	return m_obstacleData;
}
const std::vector<glm::vec2>& Obstacle::GetPositions()
{
	return m_obstacleData.positions;
}
const std::vector<size_t>& Obstacle::GetIndices()
{
	return m_obstacleData.indices;
}
const std::vector<CollisionBox>& Obstacle::GetCollisionBoxes()
{
	return m_obstacleData.collisionBoxes;
}
void Obstacle::Update(const glm::vec2& projection, const glm::vec2& camera)
{
	for (size_t i = 0; i < m_obstacleData.positions.size(); i++)
	{
		if (m_obstacleData.positions[i].x - camera.x < -m_obstacleData.sizes[m_obstacleData.indices[i]].x - m_obstacleData.generateDistance)
		{
			m_obstacleData.positions[i].x += projection.x + m_obstacleData.sizes[m_obstacleData.indices[i]].x * 2 + m_obstacleData.generateDistance;
			m_obstacleData.indices[i] = std::uniform_int_distribution<size_t>(0, m_obstacleData.textureIndices.size() > 0 ? m_obstacleData.textureIndices.size() - 1 : m_obstacleData.textureIndices.size())(m_rng);
		}
		if (m_obstacleData.positions[i].x - camera.x > m_obstacleData.sizes[m_obstacleData.indices[i]].x + projection.x + m_obstacleData.generateDistance)
		{
			m_obstacleData.positions[i].x -= projection.x + m_obstacleData.sizes[m_obstacleData.indices[i]].x * 2 + m_obstacleData.generateDistance;
			m_obstacleData.indices[i] = std::uniform_int_distribution<size_t>(0, m_obstacleData.textureIndices.size() > 0 ? m_obstacleData.textureIndices.size() - 1 : m_obstacleData.textureIndices.size())(m_rng);
		}
	}
}
void Obstacle::Render(const glm::mat4& projection, const glm::vec2& camera)
{
	glm::mat4 view = glm::mat4(1.0f);
	transform::Translate(view, -camera);
	m_shader.Bind();
	transform::SetUniformMatrix(m_shader.GetProgram(), "u_projection", projection);
	transform::SetUniformMatrix(m_shader.GetProgram(), "u_view", view);
	for (size_t i = 0; i < m_obstacleData.positions.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		m_textureManager.Bind(m_obstacleData.textureIndices[m_obstacleData.indices[i]]);
		transform::Translate(model, m_obstacleData.positions[i]);
		transform::Scale(model, m_obstacleData.sizes[m_obstacleData.indices[i]]);
		transform::SetUniformMatrix(m_shader.GetProgram(), "u_model", model);
		m_mesh.Draw();
	}
	m_textureManager.UnBind();
	m_shader.UnBind();
}
void Obstacle::Destroy()
{
	m_mesh.Destroy();
	m_shader.Destroy();
	m_textureManager.Destroy();
}