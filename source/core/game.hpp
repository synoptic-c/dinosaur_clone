#pragma once
#include"../module/gui/menu.hpp"
#include"../module/input/input_dinosaur.hpp"
#include"../module/input/input_handler.hpp"
#include"../module/scene/camera.hpp"
#include"../module/entity/dinosaur.hpp"
#include"../module/scene/ground.hpp"
#include"../module/entity/obstacle.hpp"
#include"../../engine/tool/resource_manager.hpp"
#include"../module/gui/debug_console.hpp"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<map>
#include<string>
struct GameData
{
	float cameraOffsetX;
	float cameraOffsetY;
	float projectionX;
	float projectionY;
	float scopeRange;
};
class Game
{
private:
	InputDinosaur m_dinosaurInput;
	Camera m_camera;
	Dinosaur m_dinosaur;
	Ground m_ground;
	Obstacle m_obstacle;
	GameData m_gameData;
public:
	void SetUp();
	void Create(const std::string& path);
	glm::vec2& GetCameraDebug();
	DinosaurData& GetDinosaurData();
	GroundData& GetGroundData();
	ObstacleData& GetObstacleData();
	void Update(GLFWwindow* window, float deltaTime, MenuState& menuState, bool& freeMode);
	void Render();
	void Destroy();
};