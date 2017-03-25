#include "RectF.h"

RectF::RectF(float left, float right, float top, float bottom) :
	mLeft(left),
	mRight(right),
	mTop(top),
	mBottom(bottom)
{}

RectF::RectF(const Vec2& topLeft, const Vec2& bottomRight) :
	RectF(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{}

RectF::RectF(const Vec2& topLeft, float width, float height) :
	RectF(topLeft, topLeft + Vec2(width, height))
{}

bool RectF::IsOverLapping(const RectF& other) const
{
	return mRight > other.mLeft && mLeft < other.mRight
		&& mBottom > other.mTop && mTop < other.mBottom;
}

RectF RectF::FromCenter(const Vec2& centerPosition, float halfWidth, float halfHeight)
{
	const Vec2 halfPos(halfWidth, halfHeight);
	return RectF(centerPosition - halfPos, centerPosition + halfPos);
}
