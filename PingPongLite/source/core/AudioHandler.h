#pragma once
#include "core/SDLHandler.h"
#include "interfaces/ballObserver/BallSubscriber.h"

enum class SOUNDS : char
{
	MUSIC,
	WIN,
	LOSE,
	IMPACT
};

class AudioHandler : public BallSubscriber
{
  public:
	AudioHandler() = default;
	~AudioHandler() = default;

	void init();
	void onBallEvent(BallEvent event) override;
	void close();

  protected:
  private:
	void load(std::string fileName, MIX_Mixer* mixer, MIX_Track** track) const;
	void startMusic();

	MIX_Track* music = NULL;
	MIX_Track* win = NULL;
	MIX_Track* lose = NULL;
	MIX_Track* hit = NULL;

	std::string audioAssetFolder = "assets\\sounds\\";
};
