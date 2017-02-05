/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ball( Graphics::GetScreenRect().GetCenter(),Vec2( -0.5f,-1.0f ) ),
	walls( RectF::FromCenter( Graphics::GetScreenRect().GetCenter(),fieldWidth / 2.0f,fieldHeight / 2.0f ),
		   wallThickness,wallColor ),
	soundPad( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav" ),
	soundFart( L"Sounds\\fart.wav" ),
	pad( Vec2( 400.0f,550.0f ),32.0f,6.0f )
{
	const Vec2 gridTopLeft( walls.GetInnerBounds().left,walls.GetInnerBounds().top + topSpace );
	int i = 0; 
	for( int y = 0; y < nBricksDown; y++ )
	{
		const Color c = brickColors[y];
		for( int x = 0; x < nBricksAcross; x++ )
		{
			bricks[i] = Brick( RectF(
				gridTopLeft + Vec2( x * brickWidth,y * brickHeight ),
				brickWidth,brickHeight ),c );
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while( elapsedTime > 0.0f )
	{
		const float dt = std::min( 0.0025f,elapsedTime );
		UpdateModel( dt );
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( float dt )
{
	if( gameState == 1 )
	{
		pad.Update( wnd.kbd,dt );
		pad.DoWallCollision( walls.GetInnerBounds() );

		ball.Update( dt );

		bool collisionHappened = false;
		float curColDistSq;
		int curColIndex;
		for( int i = 0; i < nBricks; i++ )
		{
			if( bricks[i].CheckBallCollision( ball ) )
			{
				const float newColDistSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();
				if( collisionHappened )
				{
					if( newColDistSq < curColDistSq )
					{
						curColDistSq = newColDistSq;
						curColIndex = i;
					}
				}
				else
				{
					curColDistSq = newColDistSq;
					curColIndex = i;
					collisionHappened = true;
				}
			}
		}

		if( collisionHappened )
		{
			pad.ResetCooldown();
			bricks[curColIndex].ExecuteBallCollision( ball );
			soundBrick.Play();
		}

		if( pad.DoBallCollision( ball ) )
		{
			soundPad.Play();
		}

		const int ballWallColResult = ball.DoWallCollision( walls.GetInnerBounds() );
		if( ballWallColResult == 1 )
		{
			pad.ResetCooldown();
			soundPad.Play();
		}
		else if( ballWallColResult == 2 )
		{
			gameState = 2;
			soundFart.Play();
		}
	}
	else if( gameState == 0 )
	{
		if( wnd.kbd.KeyIsPressed( VK_RETURN ) )
		{
			gameState = 1;
		}
	}
}

void Game::ComposeFrame()
{
	if( gameState == 1 )
	{
		ball.Draw( gfx );
		pad.Draw( gfx );
	}
	if( gameState != 0 )
	{
		for( const Brick& b : bricks )
		{
			b.Draw( gfx );
		}
		walls.Draw( gfx );
	}
	if( gameState == 0 )
	{
		SpriteCodex::DrawTitle( Graphics::GetScreenRect().GetCenter(),gfx );
	}
	else if( gameState == 2 )
	{
		SpriteCodex::DrawGameOver( Graphics::GetScreenRect().GetCenter(),gfx );
	}
}
