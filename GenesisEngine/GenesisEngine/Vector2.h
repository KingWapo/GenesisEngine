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
	Rect2D() { m_C = Vector2(); m_W = 0f; m_H = 0f; }
	Rect2D(Vector2 p_C, float p_W, float p_H) 
	{
		m_C = p_C;
		m_W = p_W;
		m_H = p_H;
	}

	~Rect2D() { }

	Vector2 getCenter() { return m_C; }
	float getWidth() { return m_W; }
	float getHeight() { return m_H; }

	void setRect(Vector2 p_C, float p_W, float p_H)
	{
		m_C = p_C;
		m_W = p_W;
		m_H = p_H;
	}

private:
	Vector2 m_C;
<<<<<<< HEAD
	Vector2 m_D;

	float width;
	float height;
=======
	float m_H;
	float m_H;
>>>>>>> origin/CollisionEnhancement
};

class Circ2D {
public:
	Circ2D() { m_C = Vector2(); m_R = 0.0f; }
	Circ2D(Vector2 p_C, float p_R)
	{
		m_C = p_C;
		m_R = p_R;
	}

	~Circ2D() { }

	Vector2 C() { return m_C; }
	float R() { return m_R; }

	void setLocation(Vector2 p_C) { m_C = p_C; }
	void setRadius(float p_R) { m_R = p_R; }

	void setCirc(Vector2 p_C, float p_R)
	{
		m_C = p_C;
		m_R = p_R;
	}

private:
	Vector2 m_C;
	float m_R;
};