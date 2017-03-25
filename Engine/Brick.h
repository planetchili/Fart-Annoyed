#pragma once
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& position, Color brickColor);
	bool BallCollision(Ball& ball);
	void DrawBrick(Graphics& gfx) const;
private:
	RectF mPosition;
	Color mBrickColor;
	bool mBrickDestroyed = false;
};