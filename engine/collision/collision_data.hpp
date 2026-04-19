#pragma once
#include<glm/glm.hpp>
#include<vector>
struct CollisionBox
{
	float left;
	float right;
	float up;
	float down;
};
struct CollisionState
{
	bool hasCollided;
	bool isObstacleCollision;
};
struct CollisionObstacle
{
	std::vector<size_t> styleIndices;
	std::vector<CollisionBox> collisionBoxes;
	std::vector<glm::vec2> positions;
	bool isObstacle;
};