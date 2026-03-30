#pragma once
#include "components/BallMovementDecorator.h"
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/Texturehandler.h"
#include "entities/Object.h"
#include "entities/interfaces/BoundaryObserver/BoundaryPublisher.h"
#include "scenes/components/PaddleHitObserver/PaddleHitSubscriber.h"
#include <algorithm>
#include <random>

class Ball : public Object, public BoundarySubscriber, public PaddleHitSubscriber
{
  public:
	Ball();
	void update() override;
	void render() override;

	virtual void onPaddleHit(const SDL_FRect& paddleCollider) override;

  private:
	virtual void onBoundaryEvent(BOUNDARY event) override;

	BallMovementDecorator movement;
};
