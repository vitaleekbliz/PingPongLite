#pragma once
#include "core/SDLHandler.h"
#include "core/subsystems/EffectHandler.h"
#include "entities/Object.h"

class EffectComponent : public Object
{
  public:
	EffectComponent();
	virtual void update() override;
	virtual void render() override;

	void start(bool color, float duration);
	void upgradeColor(bool color);

  private:
	void draw();
	EFFECT getSprite();
	void switchFrame();

	const float frameThreshold = 0.1;
	float frameTime = 0.f;

	float currentDuration = 0.f;
	float maxDuration = 0.f;

	enum State : char
	{
		OFF,
		START,
		LOOP,
		END
	} state;
	bool color = true;

	int currentFrame = 0;
	const int startFrames = 4;
	const int loopFrames = 8;
	const int endFrames = 5;
};
