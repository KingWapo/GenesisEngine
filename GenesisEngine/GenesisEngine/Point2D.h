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
