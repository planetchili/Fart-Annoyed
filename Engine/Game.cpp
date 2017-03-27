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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	walls(RectF(0.0f, (float)gfx.ScreenWidth, 0.0f, (float)gfx.ScreenHeight)),
	brickDestroy(L"Sounds\\arkbrick.wav"),
	padHit(L"Sounds\\arkpad.wav"),
	ball(Vec2(300.0f, 300.0f), Vec2(300.0f, 300.0f)),
	pad(Vec2(400.0f, 500.0f), 50.0f, 15.0f)
{
	const Color colors[4] = { Colors::Green, Colors::Cyan, Colors::Blue, Colors::Yellow };
	Vec2 topLeft(0.0f, 0.0f);
	int i = 0;

	for (int y = 0; y < brickDown; y++)
	{
		const Color c = colors[y];

		for (int x = 0; x < brickAcross; x++)
		{
			bricks[i] = Brick(RectF(
				topLeft + Vec2(x * brickWidth, y * brickHeight), 
				brickWidth, brickHeight), c);
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = delta.Mark();
	ball.Update(dt);
	pad.Update(wnd.kbd, dt);
	pad.WallCollision(walls);

	if (pad.BallCollision(ball))
	{
		padHit.Play();
	}

	for (Brick& b : bricks)
	{
		if (b.BallCollision(ball))
		{
			brickDestroy.Play();
		}
	}
	

	if (ball.WallCollision(walls))
	{
		brickDestroy.Play();
	}
}

void Game::ComposeFrame()
{
	for (const Brick& b : bricks)
	{
		b.DrawBrick(gfx);
	}

	ball.DrawBall(gfx);
	pad.Draw(gfx);
}
