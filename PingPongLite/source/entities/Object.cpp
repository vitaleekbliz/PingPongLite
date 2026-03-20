#include "Object.h"

void Object::requestDrawTexture(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip, bool isDestinationCentered)
{
	if (auto sharedSub = textureSubscriber.lock())
	{
		sharedSub->onDrawRequestTexture(texture, destination, flip, isDestinationCentered);
	}
}

void Object::requestDrawText(FONT id, std::string text, SDL_FPoint* position, int size, SDL_Color color)
{
	if (auto sharedSub = fontSubscriber.lock())
	{
		sharedSub->onDrawRequestText(id, text, position, size, color);
	}
}

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
	rect.x = position.x - size.x / 2;
	rect.y = position.y - size.y / 2;
	rect.w = size.x;
	rect.h = size.y;
	return rect;
}
