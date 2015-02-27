#pragma once

class Point2D
{
public:
	Point2D(int pX = 0, int pY = 0) { mX = pX; mY = pY; }
	~Point2D() {}

	int x() { return mX; }
	int y() { return mY; }

	int& rx() { return mX; }
	int& ry() { return mY; }

private:
	int mX, mY;
};

class Point2DF
{
public:
	Point2DF(float pX = 0, float pY = 0) { mX = pX; mY = pY; }
	~Point2DF() {}

	float x() { return mX; }
	float y() { return mY; }

	float& rx() { return mX; }
	float& ry() { return mY; }

private:
	float mX, mY;
};
