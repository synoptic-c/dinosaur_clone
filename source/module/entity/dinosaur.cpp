#include"dinosaur.hpp"
void Dinosaur::SetUp()
{
	m_dinosaurData.position = m_dinosaurDefaultData.position;
	m_dinosaurData.speed = m_dinosaurDefaultData.speed;
	m_dinosaurData.direction = m_dinosaurDefaultData.direction;
	m_dinosaurData.airTime = m_dinosaurDefaultData.airTime;
	m_dinosaurData.walkSpeed = m_dinosaurDefaultData.walkSpeed;
	m_dinosaurData.speedLimit = m_dinosaurDefaultData.speedLimit;
	m_dinosaurData.increaseSpeed = m_dinosaurDefaultData.increaseSpeed;
	m_dinosaurData.gravity = m_dinosaurDefaultData.gravity;
	m_dinosaurData.jumpSpeed = m_dinosaurDefaultData.jumpSpeed;
	m_dinosaurData.coyoteTime = m_dinosaurDefaultData.coyoteTime;
	m_dinosaurData.animationState = m_dinosaurDefaultData.animationState;
	m_dinosaurData.animationFrame = m_dinosaurDefaultData.animationFrame;
	m_dinosaurData.animationIdle = m_dinosaurDefaultData.animationIdle;
	m_dinosaurData.animationSpeed = m_dinosaurDefaultData.animationSpeed;
	m_dinosaurData.runAnimationStart = m_dinosaurDefaultData.runAnimationStart;
	m_dinosaurData.runAnimationFrameCount = m_dinosaurDefaultData.runAnimationFrameCount;
	m_dinosaurData.collisionBox = m_dinosaurDefaultData.collisionBox;
}
void Dinosaur::Create(const std::string& loadPath)
{
	std::map<std::string, std::string> resourcesPath = resourcemanager::LoadFromIni(loadPath);
	MeshData meshData;
	resourcemanager::LoadMesh({ resourcesPath["ver_path"], resourcesPath["idx_path"] }, meshData);
	m_mesh.LoadFromData(meshData);
	m_shader.LoadFromFile({ resourcesPath["vertex_path"], resourcesPath["fragment_path"] });
	m_textureManager.LoadTextures(resourcemanager::LoadFromList(resourcesPath["textures_path"]));
	m_dinosaurDefaultData.collisionBox = collisionmanager::LoadFromData(resourcesPath["collision_point_path"]);
	std::map<std::string, std::string> loadData = resourcemanager::LoadFromIni(resourcesPath["data_path"]);
	m_dinosaurDefaultData.position = glm::vec2(std::stof(loadData["position_x"]), std::stof(loadData["position_y"]));
	m_dinosaurDefaultData.speed = glm::vec2(std::stof(loadData["speed_x"]), std::stof(loadData["speed_y"]));
	m_dinosaurDefaultData.direction = std::stof(loadData["direction"]);
	m_dinosaurDefaultData.airTime = std::stof(loadData["air_time"]);
	m_dinosaurDefaultData.walkSpeed = std::stof(loadData["walk_speed"]);
	m_dinosaurDefaultData.speedLimit = std::stof(loadData["speed_limit"]);
	m_dinosaurDefaultData.increaseSpeed = std::stof(loadData["increase_speed"]);
	m_dinosaurDefaultData.gravity = std::stof(loadData["gravity"]);
	m_dinosaurDefaultData.jumpSpeed = std::stof(loadData["jump_speed"]);
	m_dinosaurDefaultData.coyoteTime = std::stof(loadData["coyote_time"]);
	m_dinosaurDefaultData.animationState = std::stoul(loadData["animation_state"]);
	m_dinosaurDefaultData.animationFrame = std::stof(loadData["animation_frame"]);
	m_dinosaurDefaultData.animationIdle = std::stoul(loadData["animation_idle"]);
	m_dinosaurDefaultData.animationSpeed = std::stof(loadData["animation_speed"]);
	m_dinosaurDefaultData.runAnimationStart = std::stoul(loadData["run_animation_start"]);
	m_dinosaurDefaultData.runAnimationFrameCount = std::stoul(loadData["run_animation_frame_count"]);
}
DinosaurData& Dinosaur::GetData()
{
	return m_dinosaurData;
}
const glm::vec2& Dinosaur::GetPosition()
{
	return m_dinosaurData.position;
}
void Dinosaur::Update(InputDinosaur& input, const std::vector<CollisionObstacle>& collisionObstacle, float deltaTime, bool& isDead)
{
	if (glm::abs(input.walk) > 0)
	{
		m_dinosaurData.direction = glm::abs(input.walk * 90.0f - 90.0f);
	}
	m_dinosaurData.speed.x = input.walk * m_dinosaurData.walkSpeed;
	if (m_dinosaurData.walkSpeed < m_dinosaurData.speedLimit)
	{
		m_dinosaurData.walkSpeed += m_dinosaurData.increaseSpeed * deltaTime;
	}
	m_dinosaurData.position.x += m_dinosaurData.speed.x * deltaTime;
	CollisionState collisionState;
	collisionmanager::CheckAndResolveCollision(glm::vec2(m_dinosaurData.speed.x, 0.0f), m_dinosaurData.collisionBox, m_dinosaurData.position, collisionObstacle, collisionState);
	if (collisionState.hasCollided == 1)
	{
		if (collisionState.isObstacleCollision == 1)
		{
			isDead = 1;
		}
		m_dinosaurData.speed.x = 0.0f;
	}
	m_dinosaurData.airTime += deltaTime;
	m_dinosaurData.speed.y -= m_dinosaurData.gravity * deltaTime;
	if (input.jump == 1 && m_dinosaurData.airTime < m_dinosaurData.coyoteTime)
	{
		m_dinosaurData.speed.y = m_dinosaurData.jumpSpeed;
	}
	m_dinosaurData.position.y += m_dinosaurData.speed.y * deltaTime;
	collisionmanager::CheckAndResolveCollision(glm::vec2(0.0f, m_dinosaurData.speed.y), m_dinosaurData.collisionBox, m_dinosaurData.position, collisionObstacle, collisionState);
	if (collisionState.hasCollided == 1)
	{
		if (collisionState.isObstacleCollision == 1)
		{
			isDead = 1;
		}
		if (m_dinosaurData.speed.y <= 0.0f)
		{
			m_dinosaurData.airTime = 0;
		}
		m_dinosaurData.speed.y = 0.0f;
	}
	m_dinosaurData.animationState = m_dinosaurData.animationIdle;
	if (glm::abs(m_dinosaurData.speed.x) > 0.0f)
	{
		m_dinosaurData.animationFrame += deltaTime * glm::abs(m_dinosaurData.speed.x) * m_dinosaurData.animationSpeed;
		m_dinosaurData.animationState = m_dinosaurData.runAnimationStart + size_t(m_dinosaurData.animationFrame) % m_dinosaurData.runAnimationFrameCount;
	}
	else
	{
		m_dinosaurData.animationFrame = 0.0f;
	}
	if (m_dinosaurData.airTime > 0)
	{
		m_dinosaurData.animationState = m_dinosaurData.animationIdle;
		m_dinosaurData.animationFrame = 0.0f;
	}
	//if (input.down == 1)
	//{
	//	m_animationState = 3;
	//	if (glm::abs(m_speed.x) > 0.0f)
	//	{
	//		m_animationFrame += deltaTime * glm::abs(m_speed.x) * 4.0f;
	//		m_animationState = 3 + size_t(m_animationFrame) % 2;
	//	}
	//}
}
void Dinosaur::Render(const glm::mat4& projection, const glm::vec2& camera, InputDinosaur& input)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	m_shader.Bind();
	m_textureManager.Bind(m_dinosaurData.animationState);
	transform::Translate(view, -camera);
	transform::Translate(model, m_dinosaurData.position);
	transform::RotateYAxis(model, m_dinosaurData.direction);
	transform::SetUniformMatrix(m_shader.GetProgram(), "u_projection", projection);
	transform::SetUniformMatrix(m_shader.GetProgram(), "u_view", view);
	transform::SetUniformMatrix(m_shader.GetProgram(), "u_model", model);
	m_mesh.Draw();
	m_shader.UnBind();
	m_textureManager.UnBind();
}
void Dinosaur::Destroy()
{
	m_mesh.Destroy();
	m_shader.Destroy();
	m_textureManager.Destroy();
}