#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDLHandler.h"
#include <string>

class Texture
{
  public:
	void setMetaData(const std::string& fileName, const std::string& baseFolder, int w, int h);
	bool loadMedia();

  protected:
	int width;
	int height;
	std::string fileName;
	std::string baseFolder;

	SDL_Texture* texture;
};
