#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(int w, int h)
{
	width = w;
	height = h;
	x = 0;
	y = 0;
}

BoxColliderComponent::~BoxColliderComponent()
{
}

SDL_FRect BoxColliderComponent::getRect() const
{
	float halfWidht = (float)width / 2;
	float halfHeight = (float)height / 2;

	return {x - halfWidht, y - halfHeight, (float)width, (float)height};
}

void BoxColliderComponent::move(int x, int y)
{
	this->x = x;
	this->y = y;
}
