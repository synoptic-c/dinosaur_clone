#pragma once
#include"../../engine/math/transform.hpp"
class Camera
{
private:
	glm::vec2 m_camera;
	glm::mat4 m_projection = glm::mat4(1.0f);
public:
	void SetProjection(const float& width, const float& height);
	void SetCamera(const glm::vec2& position);
	void MoveCamera(const glm::vec2& position);
	glm::vec2& GetCameraDebug();
	const glm::vec2& GetCamera();
	const glm::mat4& GetProjection();
};