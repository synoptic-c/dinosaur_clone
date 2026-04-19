#pragma once
#include"../../engine/renderer/mesh.hpp"
#include"../../engine/renderer/shader.hpp"
#include"../../engine/renderer/texture.hpp"
#include"../../engine/math/transform.hpp"
#include"../../engine/collision/collision_data.hpp"
#include"../../engine/collision/collision_manager.hpp"
#include"../input/input_dinosaur.hpp"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<map>
#include<string>
struct DinosaurData
{
	glm::vec2 position;
	glm::vec2 speed;
	float direction;
	float airTime;
	float walkSpeed;
	float speedLimit;
	float increaseSpeed;
	float gravity;
	float jumpSpeed;
	float coyoteTime;
	size_t animationState;
	float animationFrame;
	size_t animationIdle;
	float animationSpeed;
	size_t runAnimationStart;
	size_t runAnimationFrameCount;
	CollisionBox collisionBox;
};
class Dinosaur
{
private:
	Mesh m_mesh;
	Shader m_shader;
	TextureManager m_textureManager;
	DinosaurData m_dinosaurDefaultData;
	DinosaurData m_dinosaurData;
public:
	void SetUp();
	void Create(const std::string& loadPath);
	const glm::vec2& GetPosition();
	DinosaurData& GetData();
	void Update(InputDinosaur& input, const std::vector<CollisionObstacle>& collisionObstacle, float deltaTime, bool& isDead);
	void Render(const glm::mat4& projection, const glm::vec2& camera, InputDinosaur& input);
	void Destroy();
};