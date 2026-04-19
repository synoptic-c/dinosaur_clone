#include"camera.hpp"
void Camera::SetProjection(const float& width, const float& height)
{
	transform::Ortho(m_projection, width, height);
}
void Camera::SetCamera(const glm::vec2& position)
{
	m_camera = position;
}
void Camera::MoveCamera(const glm::vec2& position)
{
	m_camera += position;
}
glm::vec2& Camera::GetCameraDebug()
{
	return m_camera;
}
const glm::vec2& Camera::GetCamera()
{
	return m_camera;
}
const glm::mat4& Camera::GetProjection()
{
	return m_projection;
}