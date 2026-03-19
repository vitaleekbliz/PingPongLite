#pragma once
#include "BallComponents/Collision.h"
#include "BallComponents/Movement.h"
#include "Object.h"
#include "core/Texturehandler.h"
#include "interfaces/ballObserver/BallPublisher.h"
#include <algorithm>
#include <random>

class Ball : public Object, public BallPublisher, public Collision, public Movement
{
  public:
	Ball();
	void update() override;
	void render() override;

  private:
	virtual void notify(BallEvent event) override;

	void reset();
};
