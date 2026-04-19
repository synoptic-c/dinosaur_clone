#include"game.hpp"
void Game::SetUp()
{
	m_dinosaur.SetUp();
	m_ground.SetUp();
	m_obstacle.SetUp({ m_gameData.projectionX, m_gameData.projectionY });
}
void Game::Create(const std::string& loadPath)
{
	std::map<std::string, std::string> resourcesPath = resourcemanager::LoadFromIni(loadPath);
	std::map<std::string, std::string> loadData = resourcemanager::LoadFromIni(resourcesPath["game_data_path"]);
	m_camera.SetProjection(std::stof(loadData["projection_x"]), std::stof(loadData["projection_y"]));
	m_camera.SetCamera(glm::vec2(std::stof(loadData["camera_x"]), std::stof(loadData["camera_y"])));
	m_dinosaur.Create(resourcesPath["dinosaur_path"]);
	m_ground.Create(resourcesPath["ground_path"]);
	m_obstacle.Create(resourcesPath["obstacle_path"]);
	m_gameData.scopeRange = std::stof(loadData["scope_range"]);
	m_gameData.projectionX = std::stof(loadData["projection_x"]);
	m_gameData.projectionY = std::stof(loadData["projection_y"]);
	m_gameData.cameraOffsetX = std::stof(loadData["camera_offset_x"]);
	m_gameData.cameraOffsetY = std::stof(loadData["camera_offset_y"]);
}
glm::vec2& Game::GetCameraDebug()
{
	return m_camera.GetCameraDebug();
}
DinosaurData& Game::GetDinosaurData()
{
	return m_dinosaur.GetData();
}
GroundData& Game::GetGroundData()
{
	return m_ground.GetData();
}
ObstacleData& Game::GetObstacleData()
{
	return m_obstacle.GetData();
}
void Game::Update(GLFWwindow* window, float deltaTime, MenuState& menuState, bool& freeMode)
{
	inputhandler::InputPlayer(window, m_dinosaurInput, menuState, freeMode);
	m_ground.Update(m_camera.GetCamera());
	m_obstacle.Update({ m_gameData.projectionX, m_gameData.projectionY }, m_camera.GetCamera());
	m_dinosaur.Update(m_dinosaurInput, { {m_ground.GetStyleIndices(), { m_ground.GetCollisionBox() }, m_ground.GetPositions(), 0},
										 {m_obstacle.GetIndices(), m_obstacle.GetCollisionBoxes(), m_obstacle.GetPositions(), 1} }, deltaTime, menuState.isDead);
	float targetCameraY = m_dinosaur.GetPosition().y - m_gameData.cameraOffsetY;
	if (targetCameraY < m_gameData.projectionY)
	{
		targetCameraY = m_gameData.scopeRange;
	}
	m_camera.SetCamera(glm::vec2(m_dinosaur.GetPosition().x - m_gameData.cameraOffsetX, targetCameraY));
}
void Game::Render()
{
	m_dinosaur.Render(m_camera.GetProjection(), m_camera.GetCamera(), m_dinosaurInput);
	m_ground.Render(m_camera.GetProjection(), m_camera.GetCamera());
	m_obstacle.Render(m_camera.GetProjection(), m_camera.GetCamera());
}
void Game::Destroy()
{
	m_dinosaur.Destroy();
	m_ground.Destroy();
	m_obstacle.Destroy();
}