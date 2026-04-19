#pragma once
#include"../../../engine/tool/resource_manager.hpp"
#include"collision_data.hpp"
#include<glm/glm.hpp>
#include<iostream>
#include<vector>
#include<string>
#include<map>
namespace collisionmanager
{
	CollisionBox LoadFromData(const std::string& path);
	void CheckAndResolveCollision(const glm::vec2& playerSpeed, const CollisionBox& playerCollisionBox, glm::vec2& playerPosition, const std::vector<CollisionObstacle>& collisionObstacles, CollisionState& collisionState);
	void ResolveCollision(const glm::vec2& playerSpeed, const CollisionBox& playerRect, glm::vec2& playerPosition, const CollisionBox& obstacleBox, const glm::vec2& obstaclePosition, CollisionState& collisionState, bool isObstacle);
}