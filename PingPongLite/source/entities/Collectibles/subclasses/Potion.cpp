#include "Potion.h"

Potion::Potion()
{
	type = COLLECTIBLE::POTION;
}

void Potion::render()
{
	TextureHandler::get().drawTexture(TEXTURE::POTION, getCollider(), SDL_FLIP_NONE);
}
