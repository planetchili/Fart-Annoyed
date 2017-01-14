#include "Brick.h"

Brick::Brick( const RectF & rect_in,Color color_in )
	:
	rect( rect_in ),
	color( color_in )
{
}

void Brick::Draw( Graphics & gfx ) const
{
	if( !destroyed )
	{
		gfx.DrawRect( rect,color );
	}
}

bool Brick::DoBallCollision( Ball & ball )
{
	if( !destroyed && rect.IsOverlappingWith( ball.GetRect() ) )
	{
		ball.ReboundY();
		destroyed = true;
		return true;
	}
	return false;
}
