#pragma once

#include "Graphics.h"
#include "Vec2.h"

class SpriteCodex
{
public:
	// centered drawing of 14x14 sprite
	static void DrawBall( const Vec2& center,Graphics& gfx );
	// centered drawing of 200x160 sprite
	static void DrawTitle( const Vec2& center,Graphics& gfx );
	// centered drawing of 84x64 sprite
	static void SpriteCodex::DrawGameOver( const Vec2& center,Graphics& gfx );
};