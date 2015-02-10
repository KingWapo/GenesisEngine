#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Vector2.h"

class Camera2D
{
private:
	int m_ScreenWidth;
	int m_ScreenHeight;
	bool m_NeedsMatrixUpdate;
	float m_Scale;
	Vector2 m_Position;
	glm::mat4 m_CameraMatrix;
	glm::mat4 m_OrthoMatrix;


public:
	Camera2D();
	Camera2D(int p_ScreenWidth, int p_ScreenHeight);
	~Camera2D();

	void Init();
	void Init(int p_ScreenWidth, int p_ScreenHeight);
	void Update();

	Vector2 ConvertScreenToWorld(Vector2 p_ScreenCoords);

	void SetPosition(const Vector2 p_newPosition) { m_Position = p_newPosition; m_NeedsMatrixUpdate = true; }
	void SetScale(float p_newScale) { m_Scale = p_newScale; m_NeedsMatrixUpdate = true; }

	Vector2 GetPosition() { return m_Position; }
	float GetScale() { return m_Scale; }
	glm::mat4 GetCameraMatrix() { return m_CameraMatrix; }

};

