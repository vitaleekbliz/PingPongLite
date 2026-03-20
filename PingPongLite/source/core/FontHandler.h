#pragma once
#include "SDLHandler.h"
#include "interfaces/fontObserver/FontPublisher.h"

class FontHandler : public FontSubscriber
{
  public:
	FontHandler() = default;
	~FontHandler() = default;

	virtual void onDrawRequestText(SDL_FPoint* position, int size, FONT id, std::string text, SDL_Color color) override;

  private:
	void drawText(SDL_FPoint* position, int size, FONT id, std::string text, SDL_Color color);

	std::string getFontName(FONT id);

	std::string fontAssetFolder = "assets\\fonts\\";
};
