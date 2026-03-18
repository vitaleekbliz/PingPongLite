#include "AudioHandler.h"

void AudioHandler::init()
{
	MIX_Audio* musicAudio = NULL;
	MIX_Audio* winAudio = NULL;
	MIX_Audio* loseAudio = NULL;
	MIX_Audio* hitAudio = NULL;

	MIX_Mixer* mixer = SDLHandler::get().getMixer();

	musicAudio = loadAudio("music.mp3", mixer);
	winAudio = loadAudio("win.mp3", mixer);
	loseAudio = loadAudio("lose.mp3", mixer);
	hitAudio = loadAudio("hit.mp3", mixer);

	music = MIX_CreateTrack(mixer);
	win = MIX_CreateTrack(mixer);
	lose = MIX_CreateTrack(mixer);
	hit = MIX_CreateTrack(mixer);

	MIX_SetTrackAudio(music, musicAudio);
	MIX_SetTrackAudio(win, winAudio);
	MIX_SetTrackAudio(lose, loseAudio);
	MIX_SetTrackAudio(hit, hitAudio);

	if (!music || !win || !lose || !hit)
	{
		SDL_Log("Couldn't create track : %s", SDL_GetError());
		return;
	}

	startMusic();
}

void AudioHandler::onBallEvent(BallEvent event)
{
	switch (event)
	{
	case BallEvent::GOAL_LEFT:
		MIX_PlayTrack(win, 0);
		break;

	case BallEvent::GOAL_RIGHT:
		MIX_PlayTrack(lose, 0);
		break;

	case BallEvent::WALL_HIT:
	case BallEvent::PADDLE_HIT:
		MIX_PlayTrack(hit, 0);
		break;
	default:
		break;
	}
}

MIX_Audio* AudioHandler::loadAudio(std::string fileName, MIX_Mixer* mixer) const
{
	std::string basePath = SDL_GetBasePath();
	std::string fullPath = basePath + audioAssetFolder + fileName;

	MIX_Audio* audio;
	audio = MIX_LoadAudio(mixer, fullPath.c_str(), false);
	if (!audio)
	{
		SDL_Log("Couldn't load %s: %s", fullPath.c_str(), SDL_GetError());
	}

	return audio;
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
