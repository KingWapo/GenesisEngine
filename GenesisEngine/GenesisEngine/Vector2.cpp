#include "Vector2.h"
#include <math.h>

//===================================
// SETTERS
//===================================

/** DEFAULT CONSTRUCTOR **/
Vector2::Vector2() {
	x = 0.;
	y = 0.;
}

/** OVERLOADED CONSTRUCTOR **/
Vector2::Vector2(float px, float py) {
	x = px;
	y = py;
}

//===================================
// HELPERS
//===================================

/** CALCULATE THE DOT PRODUCT OF TWO VECTORS **/
float Vector2::dot(Vector2 rhs) {
	return (x * rhs.x + y * rhs.y);
}

/** CALCULATE THE UNIT VECTOR **/
Vector2 Vector2::norm() {
	float mag = this->mag();
	return Vector2(x / mag, y / mag);
}

/** CALCULATE THE MAGNITUDE **/
float Vector2::mag() {
	return sqrt(mag2());
}

/** CALCULATE THE SQUARED MAGNITUDE **/
float Vector2::mag2() {
	return (pow(x, 2) + pow(y, 2));
}

std::string Vector2::toString(){
	return "x: " + std::to_string(x) + ", y: " + std::to_string(y);
}

//===================================
// OPERATORS
//===================================

/** ADDITION **/
Vector2 operator+(Vector2 lhs, const Vector2 &rhs) {
	Vector2 out = Vector2();
	out.x = lhs.x + rhs.x;
	out.y = lhs.y + rhs.y;

	return out;
}

Vector2 operator+=(Vector2 lhs, const Vector2 &rhs) {
	Vector2 out = lhs + rhs;

	return out;
}

/** SUBTRACTION **/
Vector2 operator-(Vector2 lhs, const Vector2 &rhs) {
	Vector2 out = Vector2();
	out.x = lhs.x - rhs.x;
	out.y = lhs.y - rhs.y;

	return out;
}

Vector2 operator-=(Vector2 lhs, const Vector2 &rhs) {
	Vector2 out = lhs - rhs;

	return out;
}

/** MULTIPLICATION **/
Vector2 operator*(Vector2 lhs, const float &rhs) {
	Vector2 out = Vector2();
	out.x = lhs.x * rhs;
	out.y = lhs.y * rhs;

	return out;
}

Vector2 operator*(const float &lhs, Vector2 rhs) {
	return rhs * lhs;
}

Vector2 operator*=(Vector2 lhs, const float &rhs) {
	Vector2 out = lhs * rhs;

	return out;
}

/** DIVISION **/
Vector2 operator/(Vector2 lhs, const float &rhs) {
	Vector2 out = Vector2();
	out.x = lhs.x / rhs;
	out.y = lhs.y / rhs;

	return out;
}

Vector2 operator/=(Vector2 lhs, const float &rhs) {
	Vector2 out = lhs / rhs;

	return out;
}

/** COMPARATORS **/
bool operator==(const Vector2 &lhs, const Vector2 &rhs) {
	return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

bool operator!=(const Vector2 &lhs, const Vector2 &rhs) {
	return !(lhs == rhs);
}