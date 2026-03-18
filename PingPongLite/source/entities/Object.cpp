#include "Object.h"

Object::Object()
{
	position = {0, 0};
}

void Object::setPosition(SDL_FPoint pos)
{
	position = pos;
}

SDL_FPoint Object::getPosition() const
{
	return position;
}

SDL_FRect Object::getCollider() const
{
	SDL_FRect rect = SDL_FRect();
	rect.x = position.x - size.x / 2;
	rect.y = position.y - size.y / 2;
	rect.w = size.x;
	rect.h = size.y;
	return rect;
}
