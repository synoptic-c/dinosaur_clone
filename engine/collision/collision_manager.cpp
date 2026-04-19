#include"collision_manager.hpp"
CollisionBox collisionmanager::LoadFromData(const std::string& path)
{
	std::map<std::string, std::string> resourceData = resourcemanager::LoadFromIni(path);
	return { std::stof(resourceData["left"]), std::stof(resourceData["right"]), std::stof(resourceData["up"]), std::stof(resourceData["down"]) };
}
void collisionmanager::CheckAndResolveCollision(const glm::vec2& playerSpeed, const CollisionBox& playerCollisionBox, glm::vec2& playerPosition, const std::vector<CollisionObstacle>& collisionObstacles, CollisionState& collisionState)
{
	collisionState.hasCollided = 0;
	collisionState.isObstacleCollision = 0;
	float playerUp = playerPosition.y + playerCollisionBox.up;
	float playerDown = playerPosition.y - playerCollisionBox.down;
	float playerLeft = playerPosition.x - playerCollisionBox.left;
	float playerRight = playerPosition.x + playerCollisionBox.right;
	for (const CollisionObstacle& obstacle : collisionObstacles)
	{
		for (size_t i = 0; i < obstacle.styleIndices.size(); i++)
		{
			collisionmanager::ResolveCollision(playerSpeed, { playerLeft, playerRight, playerUp, playerDown }, playerPosition, obstacle.collisionBoxes[obstacle.styleIndices[i]], obstacle.positions[i], collisionState, obstacle.isObstacle);
		}
	}
}
void collisionmanager::ResolveCollision(const glm::vec2& playerSpeed, const CollisionBox& playerRect, glm::vec2& playerPosition, const CollisionBox& obstacleBox, const glm::vec2& obstaclePosition, CollisionState& collisionState, bool isObstacle)
{
	float obstacleUp = obstaclePosition.y + obstacleBox.up;
	float obstacleDown = obstaclePosition.y - obstacleBox.down;
	float obstacleLeft = obstaclePosition.x - obstacleBox.left;
	float obstacleRight = obstaclePosition.x + obstacleBox.right;
	if (playerRect.right > obstacleLeft && playerRect.left < obstacleRight && playerRect.down < obstacleUp && playerRect.up > obstacleDown)
	{
		if (playerRect.down < obstacleUp && playerSpeed.y < 0.0f)
		{
			playerPosition.y += obstacleUp - playerRect.down;
			collisionState.hasCollided = 1;
			if (isObstacle == 1)
			{
				collisionState.isObstacleCollision = 1;
			}
		}
		if (playerRect.up > obstacleDown && playerSpeed.y > 0.0f)
		{
			playerPosition.y -= playerRect.up - obstacleDown;
			collisionState.hasCollided = 1;
			if (isObstacle == 1)
			{
				collisionState.isObstacleCollision = 1;
			}
		}
		if (playerRect.left < obstacleRight && playerSpeed.x < 0.0f)
		{
			playerPosition.x += obstacleRight - playerRect.left;
			collisionState.hasCollided = 1;
			if (isObstacle == 1)
			{
				collisionState.isObstacleCollision = 1;
			}
		}
		if (playerRect.right > obstacleLeft && playerSpeed.x > 0.0f)
		{
			playerPosition.x -= playerRect.right - obstacleLeft;
			collisionState.hasCollided = 1;
			if (isObstacle == 1)
			{
				collisionState.isObstacleCollision = 1;
			}
		}
	}
}