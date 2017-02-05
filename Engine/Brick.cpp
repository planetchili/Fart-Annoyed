#include "Brick.h"
#include <assert.h>

Brick::Brick( const RectF & rect_in,Color color_in )
	:
	rect( rect_in ),
	destroyed( false ),
	bev( color_in )
{
}

void Brick::Draw( Graphics & gfx ) const
{
	if( !destroyed )
	{
		bev.DrawBeveledBrick( rect.GetExpanded( -padding ),bevelSize,gfx );
	}
}

bool Brick::CheckBallCollision( const Ball & ball ) const
{
	return !destroyed && rect.IsOverlappingWith( ball.GetRect() );
}

void Brick::ExecuteBallCollision( Ball & ball )
{
	assert( CheckBallCollision( ball ) );

	const Vec2 ballPos = ball.GetPosition();
	if( std::signbit( ball.GetVelocity().x ) == std::signbit( (ballPos - GetCenter()).x ) )
	{
		ball.ReboundY();
	}
	else if( ballPos.x >= rect.left && ballPos.x <= rect.right )
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}
	destroyed = true;
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}
