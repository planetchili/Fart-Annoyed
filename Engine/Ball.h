#pragma once
#include "Vec2.h"
#include "Rect.h";
#include "Graphics.h"


class Ball {

public:

	Ball(Vec2 position);

	void update(float DT, Rect& Wall);

	void draw(Graphics& gfx);

	bool touchWall(Rect& Wall);

private:

	static constexpr float size = 20.0f;

	Rect box;

	Vec2 vel{ -10,-10};

	float speed = 100.0f;
};
