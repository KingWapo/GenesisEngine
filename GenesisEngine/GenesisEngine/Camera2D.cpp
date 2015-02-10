#include "Camera2D.h"


Camera2D::Camera2D()
{
	m_Position = Vector2(0, 0);
	m_CameraMatrix = glm::mat4(1.0f);
	m_OrthoMatrix = glm::mat4(1.0f);
	m_Scale = 1.0f;
	m_NeedsMatrixUpdate = true;
	m_ScreenWidth = 500;
	m_ScreenHeight = 500;
}

Camera2D::Camera2D(int p_ScreenWidth, int p_ScreenHeight)
{
	m_Position = Vector2(0, 0);
	m_CameraMatrix = glm::mat4(1.0f);
	m_OrthoMatrix = glm::mat4(1.0f);
	m_Scale = 1.0f;
	m_NeedsMatrixUpdate = true;
	m_ScreenWidth = p_ScreenWidth;
	m_ScreenHeight = p_ScreenHeight;
}


Camera2D::~Camera2D()
{
}

void Camera2D::Init()
{
	m_OrthoMatrix = glm::ortho(0.0f, (float)m_ScreenWidth, 0.0f, (float)m_ScreenHeight);
}

void Camera2D::Init(int p_ScreenWidth, int p_ScreenHeight)
{
	m_ScreenWidth = p_ScreenWidth;
	m_ScreenHeight = p_ScreenHeight;
	Init();
}

void Camera2D::Update()
{
	if (m_NeedsMatrixUpdate)
	{
		glm::vec3 translate(-m_Position.x + m_ScreenWidth / 2, -m_Position.y + m_ScreenHeight / 2, 0.0f);
		m_CameraMatrix = glm::translate(m_OrthoMatrix, translate);

		glm::vec3 scale(m_Scale, m_Scale, 0.0f);
		m_CameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_CameraMatrix;
		m_NeedsMatrixUpdate = false;
	}
}

Vector2 Camera2D::ConvertScreenToWorld(Vector2 p_ScreenCoords)
{
	// Invert y direction
	p_ScreenCoords.y = m_ScreenHeight - p_ScreenCoords.y;

	// Center at 0
	p_ScreenCoords -= Vector2(m_ScreenWidth / 2, m_ScreenHeight / 2);

	// Scale the coordinates.
	p_ScreenCoords /= m_Scale;

	// Translate with the camera position
	p_ScreenCoords += m_Position;

	return p_ScreenCoords;
}