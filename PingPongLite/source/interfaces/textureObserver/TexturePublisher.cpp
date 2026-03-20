#include "TexturePublisher.h"

void TexturePublisher::addListener(std::weak_ptr<TextureSubscriber> listener)
{
	if (textureSubscriber.lock())
	{
		SDL_Log("Failed to subscribe listener to TexturePublisher. Already has 1 active listener");
	}

	textureSubscriber = listener;
}

void TexturePublisher::removeListener()
{
	textureSubscriber.reset();
}
