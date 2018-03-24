#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float left, float right, float top, float bottom);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width, float height);
	bool Collision(const RectF& rect) const;
public:
	float mLeft;
	float mRight;
	float mTop;
	float mBottom;
};