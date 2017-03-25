#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"

class Ball
{
public:
	Ball() = default;
	Ball(const Vec2& ballPosition, const Vec2& ballVelocity);
	void Update(float delta);
	bool WallCollision(const RectF& walls);	
	void DrawBall(Graphics& gfx) const;
private:
	void ReboundX();
	void ReboundY();
	RectF GetRect() const;
private:
	static constexpr float mRadius = 7.0f;
	Vec2 mPosition;
	Vec2 mVelocity;
};