#include "RedStar.h"

RedStar::RedStar()
{
	type = COLLECTIBLE::RED_STAR;
}

void RedStar::render()
{
	TextureHandler::get().drawTexture(TEXTURE::STAR_RED, getCollider(), SDL_FLIP_NONE);
}
