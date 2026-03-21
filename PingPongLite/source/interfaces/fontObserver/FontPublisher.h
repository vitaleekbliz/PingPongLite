#pragma once
#include "FontPublisher.h"
#include "FontSubscriber.h"
#include <memory>
#include <string>

class FontPublisher
{
  public:
	void addFontListener(std::weak_ptr<FontSubscriber> listener);
	void removeFontListener();

  protected:
	virtual void requestDrawText(FONT id, std::string text, SDL_FPoint* position, int size, SDL_Color color) = 0;
	std::weak_ptr<FontSubscriber> fontSubscriber;
};
