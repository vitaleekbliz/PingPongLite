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

  protected:
  private:
	void onBallEvent(BallEvent event) override;

	std::string audioAssetFolder = " assets/arts/";
};
