#pragma once
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/TextureHandler.h"
#include "entities/Ball/Ball.h"
#include "entities/Object.h"
#include "entities/interfaces/BoundaryObserver/BoundaryPublisher.h"
#include <memory>

class Board : public Object, public BoundaryPublisher
{
  public:
	Board();
	virtual void update() override;
	virtual void render() override;

	void setReference(std::shared_ptr<Ball> ball);

  private:
	void checkBallBoundaries();
	virtual void notify(BOUNDARY event) override;

	std::weak_ptr<Ball> ball;
};
