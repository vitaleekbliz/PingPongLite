#include "BlueStar.h"

BlueStar::BlueStar()
{
	type = COLLECTIBLE::BLUE_STAR;
}

void BlueStar::render()
{
	TextureHandler::get().drawTexture(TEXTURE::STAR_BLUE, getCollider(), SDL_FLIP_NONE);
}
