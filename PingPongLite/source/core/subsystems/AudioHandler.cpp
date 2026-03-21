#include "AudioHandler.h"

AudioHandler::~AudioHandler()
{
	close();
}

AudioHandler& AudioHandler::get()
{
	static AudioHandler instance;
	return instance;
}

void AudioHandler::init()
{
	MIX_Audio* musicAudio = NULL;
	MIX_Audio* winAudio = NULL;
	MIX_Audio* loseAudio = NULL;
	MIX_Audio* hitAudio = NULL;

	MIX_Mixer* mixer = SDLHandler::get().getMixer();

	load("music.mp3", mixer, &music);
	load("win.mp3", mixer, &win);
	load("lose.mp3", mixer, &lose);
	load("hit.mp3", mixer, &hit);

	startMusic();
}

void AudioHandler::playAudio(SOUNDS sound)
{
	switch (sound)
	{
	case SOUNDS::WIN:
		MIX_PlayTrack(win, 0);
		break;

	case SOUNDS::LOSE:
		MIX_PlayTrack(lose, 0);
		break;

	case SOUNDS::HIT:
		MIX_PlayTrack(hit, 0);
		break;
	default:
		break;
	}
}

void AudioHandler::close()
{
	MIX_DestroyTrack(music);
	MIX_DestroyTrack(win);
	MIX_DestroyTrack(lose);
	MIX_DestroyTrack(hit);
}

void AudioHandler::load(std::string fileName, MIX_Mixer* mixer, MIX_Track** track) const
{
	std::string basePath = SDL_GetBasePath();
	std::string fullPath = basePath + audioAssetFolder + fileName;

	*track = MIX_CreateTrack(mixer);
	if (!*track)
	{
		SDL_Log("Couldn't create track: %s", SDL_GetError());
		return;
	}

	MIX_Audio* audio = MIX_LoadAudio(mixer, fullPath.c_str(), false);
	if (!audio)
	{
		SDL_Log("Couldn't load %s: %s", fullPath.c_str(), SDL_GetError());
		return;
	}

	if (!MIX_SetTrackAudio(*track, audio))
	{
		SDL_Log("Couldn't set audio to track: %s", SDL_GetError());
	}

	MIX_DestroyAudio(audio);
}

void AudioHandler::startMusic()
{

	SDL_PropertiesID options = SDL_CreateProperties();
	if (!options)
	{
		SDL_Log("Couldn't create play options: %s", SDL_GetError());
		return;
	}

	SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
	MIX_PlayTrack(music, options);
	SDL_DestroyProperties(options);
}
