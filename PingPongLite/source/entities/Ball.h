#pragma once
#include "BallComponents/BallCollisionDecorator.h"
#include "BallComponents/BallMovementDecorator.h"
#include "Object.h"
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/Texturehandler.h"
#include "interfaces/ballObserver/BallPublisher.h"
#include <algorithm>
#include <random>

class Ball : public Object, public BallPublisher, public BallCollisionDecorator, public BallMovementDecorator
{
  public:
	Ball();
	void update() override;
	void render() override;

  private:
	virtual void notify(BallEvent event) override;

	// Temporary solution to change audio on strategy change
	bool originalGoal = true;

	void reset();
};
