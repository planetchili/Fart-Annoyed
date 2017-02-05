#include "Walls.h"
#include <assert.h>

Walls::Walls( const RectF& innerBounds_in,float thickness_in,Color baseColor )
	:
	innerBounds( innerBounds_in ),
	thickness( thickness_in ),
	bev( baseColor )
{
	assert( innerBounds.GetExpanded( thickness ).IsContainedBy( Graphics::GetScreenRect() ) );
}

const RectF& Walls::GetInnerBounds() const
{
	return innerBounds;
}

void Walls::Draw( Graphics& gfx ) const
{
	bev.DrawBevelFrame( innerBounds.GetExpanded( thickness ),int( thickness ),gfx );
}

