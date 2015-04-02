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
	Rect2D() { m_center = Vector2(); width = 0.0f; height = 0.0f; setVerts(); }
	Rect2D(Vector2 p_center, float p_width, float p_height)
	{
		m_center = p_center;
		width = p_width;
		height = p_height;
		setVerts();
	}

	~Rect2D() { }

	// Get the center focus of the rectangle
	Vector2 getCenter() { return m_center; }

	// Get the width and height of the rectangle
	float getWidth() { return width; }
	float getHeight() { return height; }

	// Get the Verts
	Vector2 AVert() { return m_a; }
	Vector2 BVert() { return m_b; }
	Vector2 CVert() { return m_c; }
	Vector2 DVert() { return m_d; }

	void setLocation(Vector2 p_c) { m_center = p_c; setVerts(); }
	void setWidth(float p_w) { width = p_w; halfW = width / 2; setVerts(); }
	void setHeight(float p_h) { height = p_h; halfH = height / 2; setVerts(); }
	void setRect(Vector2 p_center, float p_width, float p_height)
	{
		m_center = p_center;
		width = p_width;
		height = p_height;
		setVerts();
	}

private:
	Vector2 m_center;
	float width;
	float height;

	float halfW;
	float halfH;
	// Vertices
	Vector2 m_a;
	Vector2 m_b;
	Vector2 m_c;
	Vector2 m_d;

	// Set the location of the four vertices of the rectangle.
	void setVerts()
	{
		// A is -, - (Bottom left)
		m_a = Vector2(m_center.x - halfW, m_center.y - halfH);

		// B is -, + (Top left)
		m_b = Vector2(m_center.x - halfW, m_center.y + halfH);

		// C is +, + (Top right)
		m_c = Vector2(m_center.x + halfW, m_center.y + halfH);

		// D is +, - (Bottom right)
		m_d = Vector2(m_center.x + halfW, m_center.y - halfH);
	}
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