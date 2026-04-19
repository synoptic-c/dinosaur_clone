#include"ground.hpp"
void Ground::SetUp()
{
	m_groundData.positions.clear();
	m_groundData.positions = m_groundData.setUpPositions;
}
void Ground::Create(const std::string& loadPath)
{
	std::map<std::string, std::string> resourcesPath = resourcemanager::LoadFromIni(loadPath);
	MeshData meshData;
	resourcemanager::LoadMesh({ resourcesPath["ver_path"],resourcesPath["idx_path"] }, meshData);
	m_mesh.LoadFromData(meshData);
	m_shader.LoadFromFile({ resourcesPath["vertex_path"],resourcesPath["fragment_path"] });
	m_texture.LoadFromFile(resourcesPath["texture_path"].c_str());
	std::map<std::string, std::string> loadData = resourcemanager::LoadFromIni(resourcesPath["data_path"]);
	m_groundData.collisionBox = collisionmanager::LoadFromData(resourcesPath["collision_point_path"]);
	m_groundData.size = glm::vec2(std::stof(loadData["width"]), std::stof(loadData["height"]));
	m_groundData.collisionBox.up *= m_groundData.size.y - std::stof(loadData["up_offset"]);
	m_groundData.collisionBox.down *= m_groundData.size.y;
	m_groundData.collisionBox.left *= m_groundData.size.x;
	m_groundData.collisionBox.right *= m_groundData.size.x;
	m_groundData.spacing = std::stof(loadData["spacing"]);
	for (int i = 0; i < std::stoi(loadData["count"]); i++)
	{
		m_groundData.setUpPositions.push_back(glm::vec2(std::stof(loadData["start_x"]) * m_groundData.size.x + (std::stof(loadData["spacing"]) * i), std::stof(loadData["position_y"])));
		m_groundData.styleIndices.push_back(0);
	}
}
GroundData& Ground::GetData()
{
	return m_groundData;
}
const std::vector<size_t>& Ground::GetStyleIndices()
{
	return m_groundData.styleIndices;
}
const std::vector<glm::vec2>& Ground::GetPositions()
{
	return m_groundData.positions;
}
const CollisionBox& Ground::GetCollisionBox()
{
	return m_groundData.collisionBox;
}
void Ground::Update(const glm::vec2& camera)
{
	for (glm::vec2& position : m_groundData.positions)
	{
		if (position.x - camera.x < -m_groundData.spacing * m_groundData.size.x)
		{
			position.x += m_groundData.spacing * m_groundData.positions.size();
		}
		if (position.x - camera.x > m_groundData.spacing * m_groundData.positions.size() - m_groundData.spacing * m_groundData.size.x)
		{
			position.x -= m_groundData.spacing * m_groundData.positions.size();
		}
	}
}
void Ground::Render(const glm::mat4& projection, const glm::vec2& camera)
{
	glm::mat4 view = glm::mat4(1.0f);
	transform::Translate(view, -camera);
	m_shader.Bind();
	m_texture.Bind();
	transform::SetUniformMatrix(m_shader.GetProgram(), "u_projection", projection);
	transform::SetUniformMatrix(m_shader.GetProgram(), "u_view", view);
	for (const glm::vec2& position : m_groundData.positions)
	{
		glm::mat4 model = glm::mat4(1.0f);
		transform::Translate(model, position);
		transform::Scale(model, m_groundData.size);
		transform::SetUniformMatrix(m_shader.GetProgram(), "u_model", model);
		m_mesh.Draw();
	}
	m_texture.UnBind();
	m_shader.UnBind();
}
void Ground::Destroy()
{
	m_mesh.Destroy();
	m_shader.Destroy();
	m_texture.Destroy();
}