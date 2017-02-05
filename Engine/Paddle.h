#pragma once

#include "Ball.h"
#include "Vec2.h"
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle( const Vec2& pos_in,float halfWidth_in,float halfHeight_in );
	void Draw( Graphics& gfx ) const;
	bool DoBallCollision( Ball& ball );
	void DoWallCollision( const RectF& walls );
	void Update( const Keyboard& kbd,float dt );
	RectF GetRect() const;
	void ResetCooldown();
private:
	static constexpr Color wingColor = { 210,255,210 };
	static constexpr Color color = { 200,220,200 };
	static constexpr float wingWidth = 6.0f;
	static constexpr float speed = 360.0f;
	// control the paddle rebound behavior here
	static constexpr float maximumExitRatio = 2.6f;
	static constexpr float fixedZoneWidthRatio = 0.2f;
	// ----------------------------------------
	float halfWidth;
	float halfHeight;
	// these are derived from above controls
	float exitXFactor;
	float fixedZoneHalfWidth;
	float fixedZoneExitX;
	// -------------------------------------
	Vec2 pos;
	bool isCooldown = false;
};