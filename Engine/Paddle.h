#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Keyboard.h"
#include "RectF.h"
#include "Ball.h"

class Paddle
{
public:
	Paddle() = default;
	Paddle(Vec2 pos, float halfWidth, float halfHeight);
	void Update(const Keyboard& kbd, float delta);
	void WallCollision(const RectF& walls);
	bool BallCollision(Ball& ball);
	void Draw(Graphics& gfx) const;
	RectF GetRect() const;
private:
	Vec2 mPosition;
	float mHalfWidth;
	float mHalfHeight;
	static constexpr float mSpeed = 300.0f;
	Color mColor;
};