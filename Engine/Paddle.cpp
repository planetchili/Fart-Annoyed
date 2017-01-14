#include "Paddle.h"

Paddle::Paddle( const Vec2 & pos_in,float halfWidth_in,float halfHeight_in )
	:
	pos( pos_in ),
	halfWidth( halfWidth_in ),
	halfHeight( halfHeight_in )
{
}

void Paddle::Draw( Graphics & gfx ) const
{
	RectF rect = GetRect();
	gfx.DrawRect( rect,wingColor );
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect( rect,color );
}

bool Paddle::DoBallCollision( Ball & ball ) const
{
	if( ball.GetVelocity().y > 0.0f && GetRect().IsOverlappingWith( ball.GetRect() ) )
	{
		ball.ReboundY();
		return true;
	}
	return false;	
}

void Paddle::DoWallCollision( const RectF & walls )
{
	const RectF rect = GetRect();
	if( rect.left < walls.left )
	{
		pos.x += walls.left - rect.left;
	}
	else if( rect.right > walls.right )
	{
		pos.x -= rect.right - walls.right;
	}
}

void Paddle::Update( const Keyboard & kbd,float dt )
{
	if( kbd.KeyIsPressed( VK_LEFT ) )
	{
		pos.x -= speed * dt;
	}
	if( kbd.KeyIsPressed( VK_RIGHT ) )
	{
		pos.x += speed * dt;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter( pos,halfWidth,halfHeight );
}
