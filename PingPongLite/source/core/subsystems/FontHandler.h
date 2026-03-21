#pragma once
#include "core/SDLHandler.h"
#include "interfaces/fontObserver/FontPublisher.h"

class FontHandler : public FontSubscriber
{
  public:
	FontHandler() = default;
	~FontHandler() = default;

	virtual void onDrawRequestText(FONT id, std::string text, SDL_FPoint* position, int size, SDL_Color color) override;

  private:
	void drawText(FONT id, std::string text, SDL_FPoint* position, int size, SDL_Color color);

	std::string getFontName(FONT id);

	std::string fontAssetFolder = "assets\\fonts\\";
};
