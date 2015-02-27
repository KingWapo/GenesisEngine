#pragma once

#include "Vector2.h"

class Transformation2d
{
private:
	Vector2		location;
	float		rotation;

	Vector2 translation;
	Vector2 scale;

public:
	Transformation2d();
	Transformation2d(Vector2 pLocation, float pRotation);
	~Transformation2d();

	Vector2 GetLocation() const { return location; }
	void SetLocation(Vector2 newLocation) { location = newLocation; }

	Vector2 GetWorldLoction() const {
		// compute world location by applying translation, rotation and scale
	}

	float GetRotation() const { return rotation; }
	void SetRotation(float newRotation);

	Vector2 getTranslation() { return translation; }
	void setTranslation(Vector2 p_translation) { translation = p_translation; }
	void setTranslation(float p_tX, float p_tY) { setTranslation(Vector2(p_tX, p_tY)); }

	Vector2 getScale() { return scale; }
	void setScale(Vector2 p_scale) { scale = p_scale; }
	void setScale(float p_tX, float p_tY) { setScale(Vector2(p_tX, p_tY)); }

};