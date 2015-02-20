#pragma once

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
	std::string toString();

	// operators

	// addition
	friend Vector2 operator+(Vector2 lhs, const Vector2 &rhs);
	friend Vector2 operator+=(Vector2 lhs, const Vector2 &rhs);
	// subtraction
	friend Vector2 operator-(Vector2 lhs, const Vector2 &rhs);
	friend Vector2 operator-=(Vector2 lhs, const Vector2 &rhs);
	// multiplication
	friend Vector2 operator*(Vector2 lhs, const float &rhs);
	friend Vector2 operator*(const float &lhs, Vector2 rhs);
	friend Vector2 operator*=(Vector2 lhs, const float &rhs);
	// division
	friend Vector2 operator/(Vector2 lhs, const float &rhs);
	friend Vector2 operator/=(Vector2 lhs, const float &rhs);
	// comparators
	friend bool operator==(const Vector2 &lhs, const Vector2 &rhs);
	friend bool operator!=(const Vector2 &lhs, const Vector2 &rhs);
protected:
private:
};