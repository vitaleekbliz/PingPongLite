#pragma once
#include "BallComponents/BallCollisionDecorator.h"
#include "BallComponents/BallMovementDecorator.h"
#include "Object.h"
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/Texturehandler.h"
#include "interfaces/ballObserver/BallPublisher.h"
#include <algorithm>
#include <random>

class Ball : public Object, public BallPublisher
{
  public:
	Ball();
	void update() override;
	void render() override;

	void setPaddleReferences(std::shared_ptr<Object> player, std::shared_ptr<Object> computer);

  private:
	virtual void notify(BallEvent event) override;
	void reset();

	BallCollisionDecorator player, computer;
	BallMovementDecorator movement;

	bool isCollidingPaddle = false;

	// Temporary solution to change audio on strategy change
	bool originalGoal = true;
};
