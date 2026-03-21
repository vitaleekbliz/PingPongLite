#pragma once
#include "core/SDLHandler.h"

enum class FONT : char
{
	CALIBRI
};

class FontHandler
{
  public:
	FontHandler(const FontHandler&) = delete;
	FontHandler& operator=(const FontHandler&) = delete;
	static FontHandler& get();

	void init();
	void close();

	void drawText(FONT id, std::string text, SDL_FPoint* position, int size, SDL_Color color);

  private:
	FontHandler() = default;
	~FontHandler();
	std::string getFontName(FONT id);

	std::string fontAssetFolder = "assets\\fonts\\";
};
