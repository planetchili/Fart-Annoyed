#include "Ball.h"

Ball::Ball(Vec2 position)
{
	box = Rect(position, size, size);
}


bool Ball::touchWall(Rect& Wall)
{

	bool touch = false;
	if (box.get_left() < Wall.get_left())
	{
		box.move(Vec2{ Wall.get_left() - box.get_left() ,0.0f } );

		vel.x *= -1;
		touch = true;
	}
	if (box.get_right() > Wall.get_right())
	{
		box.move(Vec2{ Wall.get_right() - box.get_right() ,0.0f });

		vel.x *= -1;
		touch = true;
	}
	if (box.get_top() < Wall.get_top()) 
	{
		box.move(Vec2{0.0f, Wall.get_top() - box.get_top() });

		vel.y *= -1;
		touch = true;
	}
	if (box.get_bottom() > Wall.get_bottom())
	{
		box.move(Vec2{ 0.0f, Wall.get_bottom() - box.get_bottom() });

		vel.y *= -1;
		touch = true;
	}

	if (touch) {
		return true;
	}
	return false;
}


void Ball::update(float DT, Rect& Wall)
{

	box.move(vel.Normalize() * speed * DT);
	touchWall(Wall);
}

void Ball::draw(Graphics& gfx)
{
	box.draw(gfx);
}
