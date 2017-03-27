#include "Brick.h"

Brick::Brick(const RectF& position, Color brickColor) :
	mPosition(position),
	mBrickColor(brickColor)
{
}

bool Brick::BallCollision(Ball& ball)
{
	if (!mBrickDestroyed && mPosition.IsOverLapping(ball.GetRect() ))
	{
		ball.ReboundY();
		mBrickDestroyed = true;

		return true;
	}

	return false;
}

void Brick::DrawBrick(Graphics& gfx) const
{
	if (!mBrickDestroyed)
	{
		gfx.DrawRect(mPosition.GetExpanded(-padding), mBrickColor);
	}
}