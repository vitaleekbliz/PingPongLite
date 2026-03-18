#include "TexturePublisher.h"

void TexturePublisher::addListener(std::weak_ptr<TextureSubscriber> listener)
{
	if (subscriber.lock())
	{
		SDL_Log("Failed to subscribe listener to TexturePublisher. Already has 1 active listener");
	}

	subscriber = listener;
}

void TexturePublisher::removeListener()
{
	subscriber.reset();
}
