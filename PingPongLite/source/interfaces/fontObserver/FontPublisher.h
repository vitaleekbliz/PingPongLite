#pragma once
#include "FontPublisher.h"
#include "FontSubscriber.h"
#include <memory>
#include <string>

class FontPublisher
{
  public:
	void addListener(std::weak_ptr<FontSubscriber> listener);
	void removeListener();

  protected:
	virtual void requestDrawText(SDL_FPoint* position, int size, FONT id, std::string text, SDL_Color color) = 0;
	std::weak_ptr<FontSubscriber> fontSubscriber;
};
