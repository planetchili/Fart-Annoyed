#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"


class Rect {
	
public:
	Rect() = default;

	Rect(Vec2& start, float width, float height, Color c_ = {255,255,255});

	void rebound_left(float changes);
	void rebound_right(float changes);
	void rebound_top(float changes);
	void rebound_bottom(float changes);

	void rebound_width(float changes);
	void rebound_height(float changes);

	void move(Vec2& move_by);

	void color(Color new_c);

	bool RectOverlap(Rect rhs);

	void draw(Graphics& gfx);

	bool is_active() const;
	void toggle_active();

	float get_top();
	float get_bottom();
	float get_left();
	float get_right();

private:

	float top;
	float bottom;
	float left;
	float right;

	float angle = 0;

	float half_width;
	float half_height;
	Vec2 center;

	bool active = 1;
	Color c = {255,255,255};


};