#pragma once
#include "components/CollisionDetector/CollisionDetector.h"
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/EffectHandler.h"
#include "core/subsystems/FontHandler.h"
#include "core/subsystems/TextureHandler.h"
#include "entities/Ball/Ball.h"
#include "entities/Board/Board.h"
#include "entities/Object.h"
#include "entities/Paddle/Paddle.h"
#include "entities/Score/ScoreBar.h"
#include "entities/interfaces/BoundaryObserver/BoundaryPublisher.h"
#include "scenes/Scene.h"
#include <memory>
#include <vector>

class MainScene : public Scene
{
  public:
	virtual void update() override;
	virtual void render() override;

	virtual void init() override;
	virtual void close() override;

  private:
	std::shared_ptr<Board> board;
	std::shared_ptr<Ball> ball;
	std::shared_ptr<ScoreBar> scoreBar;
	std::shared_ptr<Paddle> paddleLeft;
	std::shared_ptr<Paddle> paddleRight;

	std::shared_ptr<CollisionDetector> collisionDetector;
};
