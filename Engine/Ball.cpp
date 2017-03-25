#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2& ballPosition, const Vec2& ballVelocity) :
	mPosition(ballPosition),
	mVelocity(ballVelocity)
{}

void Ball::Update(float delta)
{
	mPosition += mVelocity * delta;
}

bool Ball::WallCollision(const RectF& walls)
{
	const RectF rect = GetRect();
	bool collided = false;

	if (rect.mLeft < walls.mLeft)
	{
		mPosition.x += walls.mLeft - rect.mLeft;
		ReboundX();
		collided = true;
	}
	else if (rect.mRight > walls.mRight)
	{
		mPosition.x -= rect.mRight - walls.mRight;
		ReboundX();
		collided = true;
	}

	if (rect.mTop < walls.mTop)
	{
		mPosition.y += walls.mTop - rect.mTop;
		ReboundY();
		collided = true;
	}
	else if (rect.mBottom > walls.mBottom)
	{
		mPosition.y -= rect.mBottom - walls.mBottom;
		ReboundY();
		collided = true;
	}

	return collided;
}

void Ball::ReboundX()
{
	mVelocity.x = -mVelocity.x;
}

void Ball::ReboundY()
{
	mVelocity.y = -mVelocity.y;
}

void Ball::DrawBall(Graphics& gfx) const
{
	SpriteCodex::DrawBall(mPosition, gfx);
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(mPosition, mRadius, mRadius);
}
