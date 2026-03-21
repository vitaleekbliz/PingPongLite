#include "FontPublisher.h"

void FontPublisher::addFontListener(std::weak_ptr<FontSubscriber> listener)
{
	if (fontSubscriber.lock())
	{
		SDL_Log("Failed to subscribe listener to TexturePublisher. Already has 1 active listener");
	}

	fontSubscriber = listener;
}

void FontPublisher::removeFontListener()
{
	fontSubscriber.reset();
}
