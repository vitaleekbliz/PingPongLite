#include "TexturePublisher.h"

void TexturePublisher::addTextureListener(std::weak_ptr<TextureSubscriber> listener)
{
	if (textureSubscriber.lock())
	{
		SDL_Log("Failed to subscribe listener to TexturePublisher. Already has 1 active listener");
	}

	textureSubscriber = listener;
}

void TexturePublisher::removeTextureListener()
{
	textureSubscriber.reset();
}
