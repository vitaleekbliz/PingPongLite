#pragma once
#define SDL_MAIN_HANDLED
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_image/SDL_image.h"
#include <string>

class SDLHandler
{
  public:
	SDLHandler(const SDLHandler&) = delete;
	SDLHandler& operator=(const SDLHandler&) = delete;
	static SDLHandler& get();

	bool init();
	bool handleEvents();
	void handleTickRate();
	float getTick() const;
	void close();

	SDL_Renderer* getRenderer();

	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

  private:
	SDLHandler();
	~SDLHandler();

	Uint64 lastTick;
	float deltaTime;

	const char* WINDOW_TITLE = "Ping Pong Lite";

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
};
