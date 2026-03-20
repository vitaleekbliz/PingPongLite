#pragma once
#include <SDL3/SDL.h>
#include <string>

enum class FONT : char
{
	CALIBRI
};

class FontSubscriber
{
  public:
	virtual ~FontSubscriber() = default;
	virtual void onDrawRequestText(FONT id,std::string text, SDL_FPoint* position, int size,  SDL_Color color) = 0;
};