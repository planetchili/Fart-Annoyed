#include "Paddle.h"

Paddle::Paddle(Vec2 pos, float halfWidth, float halfHeight) :
	mPosition(pos),
	mHalfWidth(halfWidth),
	mHalfHeight(halfHeight)
{}

void Paddle::Update(const Keyboard& kbd, float delta)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		mPosition.x -= mSpeed * delta;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		mPosition.x += mSpeed * delta;
	}
}

void Paddle::WallCollision(const RectF& walls)
{
	const RectF padRect = GetRect();

	if (padRect.mLeft < walls.mLeft)
	{
		mPosition.x += walls.mLeft - padRect.mLeft;
	}
	else if (padRect.mRight > walls.mRight)
	{
		mPosition.x -= padRect.mRight - walls.mRight;
	}
}

bool Paddle::BallCollision(Ball& ball)
{
	const RectF padRect = GetRect();

	if (ball.GetVelocity().y > 0 && padRect.IsOverLapping(ball.GetRect()))
	{
		ball.ReboundY();
		return true;
	}

	return false;
}

void Paddle::Draw(Graphics& gfx) const
{
	RectF padRect = GetRect();
	gfx.DrawRect(padRect, Colors::Red);
	padRect.mLeft += wingWidth;
	padRect.mRight -= wingWidth;
	gfx.DrawRect(padRect, Colors::White);
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(mPosition, mHalfWidth, mHalfHeight);
}
