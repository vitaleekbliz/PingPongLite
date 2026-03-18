#pragma once
#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
// #include <SDL3_ttf/SDL_ttf.h>
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
	MIX_Mixer* getMixer();

	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

  private:
	SDLHandler();
	~SDLHandler();

	Uint64 lastTick;
	float deltaTime;

	const char* WINDOW_TITLE = "Ping Pong Lite";

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	MIX_Mixer* mixer = NULL;
};
