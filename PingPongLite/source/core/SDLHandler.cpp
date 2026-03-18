#include "SDLHandler.h"

SDLHandler& SDLHandler::get()
{
	static SDLHandler instance;
	return instance;
}

bool SDLHandler::handleEvents()
{
	// returns false if exit game
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			return false;
			break;
		}
	}
	return true;
}

void SDLHandler::handleTickRate()
{
	Uint64 nowTick = SDL_GetTicks();
	deltaTime = (float)(nowTick - lastTick) / 1000.f;
	lastTick = nowTick;
}

float SDLHandler::getTick() const
{
	return deltaTime;
}

bool SDLHandler::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALWAYS_ON_TOP, &window,
								&renderer);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	if (!MIX_Init())
	{
		SDL_Log("Couldn't init SDL_mixer library: %s", SDL_GetError());
		return false;
	}

	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

	if (mixer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void SDLHandler::close()
{
	if (mixer)
		MIX_DestroyMixer(mixer);

	if (renderer)
		SDL_DestroyRenderer(renderer);

	if (window)
		SDL_DestroyWindow(window);
}

SDL_Renderer* SDLHandler::getRenderer()
{
	return renderer;
}

MIX_Mixer* SDLHandler::getMixer()
{
	return mixer;
}

SDLHandler::SDLHandler()
{
	lastTick = SDL_GetTicks();
	deltaTime = 0;
}
