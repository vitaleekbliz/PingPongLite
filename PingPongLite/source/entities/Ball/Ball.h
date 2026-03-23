#pragma once
#include "components/BallCollisionDecorator.h"
#include "components/BallMovementDecorator.h"
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/Texturehandler.h"
#include "entities/Object.h"
#include "entities/interfaces/BoundaryObserver/BoundaryPublisher.h"
#include <algorithm>
#include <random>

class Ball : public Object, public BoundarySubscriber
{
  public:
	Ball();
	void update() override;
	void render() override;

	void setPaddleReferences(std::shared_ptr<Object> player, std::shared_ptr<Object> computer);

  private:
	virtual void onBoundaryEvent(BOUNDARY event) override;
	void reset();

	BallCollisionDecorator player, computer;
	BallMovementDecorator movement;

	bool isCollidingPaddle = false;
};
