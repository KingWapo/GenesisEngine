#pragma once

#include "Point2D.h"
#include <string>

class Vector2 {
public:
	// constructors
	Vector2();
	Vector2(float px, float py);

	// member variables
	float x;
	float y;

	// computations
	float dot(Vector2 rhs);
	Vector2 norm();
	float mag();
	float mag2();

	// information
	Point2DF toPoint2DF();
	std::string toString();

	// operators

	// addition
	friend Vector2 operator+(const Vector2& lhs, const Vector2 &rhs);
	friend Vector2& operator+=(Vector2& lhs, const Vector2 &rhs);
	// subtraction
	friend Vector2 operator-(const Vector2& lhs, const Vector2 &rhs);
	friend Vector2& operator-=(Vector2& lhs, const Vector2 &rhs);
	// multiplication
	friend Vector2 operator*(const Vector2& lhs, const float &rhs);
	friend Vector2 operator*(const float &lhs, const Vector2& rhs);
	friend Vector2& operator*=(Vector2& lhs, const float &rhs);
	// division
	friend Vector2 operator/(const Vector2& lhs, const float &rhs);
	friend Vector2& operator/=(Vector2& lhs, const float &rhs);
	// comparators
	friend bool operator==(const Vector2 &lhs, const Vector2 &rhs);
	friend bool operator!=(const Vector2 &lhs, const Vector2 &rhs);
protected:
private:
};

class Rect2D {
public:
	Rect2D() { m_x = 0.0f; m_y = 0.0f; m_w = 0.0f; m_h = 0.0f; }
	Rect2D(float p_x, float p_y, float p_w, float p_h) 
	{
		m_x = p_x;
		m_y = p_y;
		m_w = p_w;
		m_h = p_h;
	}

	~Rect2D() { }

	float x() { return m_x; }
	float y() { return m_y; }
	float w() { return m_w; }
	float h() { return m_h; }

	void setLocation(float p_x, float p_y) { m_x = p_x; m_y = p_y; }
	void setDimensions(float p_w, float p_h) { m_w = p_w; m_h = p_h; }

	void setRect(float p_x, float p_y, float p_w, float p_h)
	{
		m_x = p_x;
		m_y = p_y;
		m_w = p_w;
		m_h = p_h;
	}

private:
	float m_x;
	float m_y;
	float m_w;
	float m_h;
};

class Circ2D {
public:
	Circ2D() { m_x = 0.0f; m_y = 0.0f; m_r = 0.0f; }
	Circ2D(float p_x, float p_y, float p_r)
	{
		m_x = p_x;
		m_y = p_y;
		m_r = p_r;
	}

	~Circ2D() { }

	float x() { return m_x; }
	float y() { return m_y; }
	float r() { return m_r; }

	float setLocation(float p_x, float p_y) { m_x = p_x; m_y = p_y; }
	float setRadius(float p_r) { m_r = p_r; }

	void setCirc(float p_x, float p_y, float p_r)
	{
		m_x = p_x;
		m_y = p_y;
		m_r = p_r;
	}

private:
	float m_x;
	float m_y;
	float m_r;
};