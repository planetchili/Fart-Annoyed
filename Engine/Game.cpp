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
	walls( RectF::FromCenter( Graphics::GetScreenRect().GetCenter(),fieldWidth / 2.0f,fieldHeight / 2.0f ),
		   wallThickness,wallColor ),
	soundPad( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav" ),
	soundFart( L"Sounds\\fart.wav" ),
	soundReady( L"Sounds\\ready.wav" ),
	pad( Vec2( 400.0f,550.0f ),32.0f,6.0f ),
	lifeCounter( { 30.0f,30.0f },3 )
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
	ResetBall();
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
			// only reset cooldown if not still coliding with ball
			// (helps prevent weird shit when ball is trapped against wall)
			if( !pad.GetRect().IsOverlappingWith( ball.GetRect() ) )
			{
				pad.ResetCooldown();
			}
			soundPad.Play();
		}
		else if( ballWallColResult == 2 )
		{
			StartRound();
			ResetBall();
			soundFart.Play();
		}
	}
	else if( gameState == 0 )
	{
		// wait on title screen until enter is pressed
		if( wnd.kbd.KeyIsPressed( VK_RETURN ) )
		{
			StartRound();
		}
	}
	else if( gameState == 3 )
	{
		// check to see if ready wait period is over
		if( (curWaitTime += dt) > readyWaitTime )
		{
			gameState = 1;
		}
	}
}

// enter ready wait for new round if there are lives, otherwise end game
void Game::StartRound()
{
	if( lifeCounter.ConsumeLife() )
	{
		curWaitTime = 0.0f;
		soundReady.Play();
		gameState = 3;
	}
	else
	{
		gameState = 2;
	}
}

void Game::ResetBall()
{
	ball = Ball( Graphics::GetScreenRect().GetCenter(),Vec2( -0.55f,-1.0f ) );
}

void Game::ComposeFrame()
{
	// draw pad and life counter if playing or waiting
	if( gameState == 1 || gameState == 3 )
	{
		pad.Draw( gfx );
		lifeCounter.Draw( gfx );
	}
	// draw ball only if playing
	if( gameState == 1 )
	{
		ball.Draw( gfx );
	}
	// draw bricks and wall always, except for title screen
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
	else if( gameState == 3 )
	{
		SpriteCodex::DrawReady( Graphics::GetScreenRect().GetCenter(),gfx );
	}
}
