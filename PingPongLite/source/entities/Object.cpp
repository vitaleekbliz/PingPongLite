#include "Object.h"

void Object::setPosition(SDL_FPoint pos)
{
	position = pos;
}

const SDL_FPoint* Object::getPosition()
{
	return &position;
}

void Object::setSize(SDL_FPoint size)
{
	this->size = size;
}

const SDL_FPoint* Object::getSize()
{
	return &size;
}

SDL_FRect Object::getCollider() const
{
	SDL_FRect rect = SDL_FRect();
	rect.x = position.x;
	rect.y = position.y;
	rect.w = size.x;
	rect.h = size.y;
	return rect;
}
