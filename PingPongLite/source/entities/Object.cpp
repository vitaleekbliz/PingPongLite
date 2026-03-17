#include "Object.h"

Object::Object()
{
	position = {0, 0};
}

void Object::setPosition(SDL_FPoint pos)
{
	position = pos;
}

SDL_FPoint Object::getPosition()
{
	return position;
}
