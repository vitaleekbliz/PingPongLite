#pragma once
#include "BallComponents/BallCollision.h"
#include "BallComponents/BallMovement.h"
#include "Object.h"
#include "core/Texturehandler.h"
#include "interfaces/ballObserver/BallPublisher.h"
#include <algorithm>
#include <random>

class Ball : public Object, public BallPublisher, public BallCollision, public BallMovement
{
  public:
	Ball();
	void update() override;
	void render() override;

  private:
	virtual void notify(BallEvent event) override;

	void reset();
};
