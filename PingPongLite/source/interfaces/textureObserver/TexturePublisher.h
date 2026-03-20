#pragma once
#include "TextureSubscriber.h"
#include <SDL3/SDL.h>
#include <memory>

class TexturePublisher
{
  public:
	void addListener(std::weak_ptr<TextureSubscriber> listener);
	void removeListener();

  protected:
	virtual void requestDrawTexture(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip,
									bool isDestinationCentered = false) = 0;
	std::weak_ptr<TextureSubscriber> textureSubscriber;
};
