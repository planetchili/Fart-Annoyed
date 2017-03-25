#pragma once
#include "Vec2.h"
/*//////////////////////////////////////////////////////
// RectF class just in case you are using using many  //
// rectangles in your game. Easier to check collision //
// and draw the boundaries with a rectangle           //
//                                                    //
//                                                   //
//////////////////////////////////////////////////////*/

class RectF
{
public:
	RectF() = default;
	RectF(float left, float right, float top, float bottom);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width, float height);
	bool IsOverLapping(const RectF& rect) const;
	static RectF FromCenter(const Vec2& centerPosition, float halfWidth, float halfHeight);
public:
	float mLeft;
	float mRight;
	float mTop;
	float mBottom;
};