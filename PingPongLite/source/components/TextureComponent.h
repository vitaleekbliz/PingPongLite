#pragma once
#include "core/SDLHandler.h"
#include <string>

class TextureComponent
{
  public:
	TextureComponent(const std::string& fileName, int w, int h);
	~TextureComponent();
	void draw(SDL_FRect destination, SDL_FlipMode flipMode, bool centerImage = true);

  private:
	bool loadMedia();

	int width;
	int height;
	SDL_Texture* texture;

	std::string fileName;
	const std::string baseFolder = "assets/arts/";
};
