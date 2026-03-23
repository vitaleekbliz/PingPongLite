#pragma once
#include "core/SDLHandler.h"

enum class SOUNDS : char
{
	MUSIC,
	WIN,
	LOSE,
	HIT
};

class AudioHandler
{
  public:
	AudioHandler(const AudioHandler&) = delete;
	AudioHandler& operator=(const AudioHandler&) = delete;
	static AudioHandler& get();

	void init();
	void playAudio(SOUNDS sound);
	void close();

  protected:
  private:
	AudioHandler() = default;
	~AudioHandler();

	void load(std::string fileName, MIX_Track** track) const;
	void startMusic();

	MIX_Track* music = NULL;
	MIX_Track* win = NULL;
	MIX_Track* lose = NULL;
	MIX_Track* hit = NULL;

	std::string audioAssetFolder = "assets\\sounds\\";
};
