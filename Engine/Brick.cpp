#include "Brick.h"

Brick::Brick(const RectF& position, Color brickColor) :
	mPosition(position),
	mBrickColor(brickColor)
{
}

void Brick::DrawBrick(Graphics& gfx) const
{
	if (!mBrickDestroyed)
	{
		gfx.DrawRect(mPosition, mBrickColor);
	}
}
