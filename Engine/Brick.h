#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"
#include "Beveler.h"

class Brick
{
public:
	Brick() = default;
	Brick( const RectF& rect_in,Color color_in );
	void Draw( Graphics& gfx ) const;
	bool CheckBallCollision( const Ball& ball ) const;
	void ExecuteBallCollision( Ball& ball );
	Vec2 GetCenter() const;
private:
	static constexpr float padding = 0.5f;
	static constexpr int bevelSize = 3;
	Beveler bev;
	RectF rect;
	bool destroyed = true;
};