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
	Rect2D() { m_A = Vector2(); m_B = Vector2(); m_C = Vector2(); m_D = Vector2(); }
	Rect2D(Vector2 p_A, Vector2 p_B, Vector2 p_C, Vector2 p_D) 
	{
		m_A = p_A;
		m_B = p_B;
		m_C = p_C;
		m_D = p_D;
	}

	~Rect2D() { }

	Vector2 A() { return m_A; }
	Vector2 B() { return m_B; }
	Vector2 C() { return m_C; }
	Vector2 D() { return m_D; }

	void setRect(Vector2 p_A, Vector2 p_B, Vector2 p_C, Vector2 p_D)
	{
		m_A = p_A;
		m_B = p_B;
		m_C = p_C;
		m_D = p_D;
	}

private:
	Vector2 m_A;
	Vector2 m_B;
	Vector2 m_C;
	Vector2 m_D;

	float width;
	float height;
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