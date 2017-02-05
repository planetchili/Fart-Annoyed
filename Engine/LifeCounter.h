#pragma once

#include "SpriteCodex.h"
#include "Graphics.h"
#include <algorithm>

class LifeCounter
{
public:
	LifeCounter( Vec2 pos,int lives )
		:
		pos( pos ),
		lives( lives )
	{}
	// returns false if there was no life remaining to consume
	bool ConsumeLife()
	{
		const bool hasLife = lives > 0;
		lives = std::max( lives - 1,0 );
		return hasLife;
	}
	void Draw( Graphics& gfx ) const
	{
		const Vec2 offset( spacing,0.0f );
		for( int c = 0; c < lives; c++ )
		{
			SpriteCodex::DrawPoo( pos + offset * float( c ),gfx );
		}
	}
private:
	static constexpr float spacing = 28.0f;
	int lives;
	Vec2 pos;
};