#include "RectF.h"

RectF::RectF(float left, float right, float top, float bottom)
	:
	mLeft(left),
	mRight(right),
	mTop(top),
	mBottom(bottom)
{}

RectF::RectF(const Vec2& topLeft, const Vec2& bottomRight)
{
	RectF(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

RectF::RectF(const Vec2& topLeft, float width, float height)
{
	RectF(topLeft, Vec2(width, height));
}

bool RectF::Collision(const RectF& rect) const
{
	return this->mLeft <= rect.mRight && this->mRight >= rect.mLeft
		&& this->mTop >= rect.mBottom && this->mBottom <= rect.mBottom;
}
