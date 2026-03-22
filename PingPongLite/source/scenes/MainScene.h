#pragma once
#include "components/objectFactory/Creator.h"
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/FontHandler.h"
#include "core/subsystems/TextureHandler.h"
#include "entities/interfaces/ballObserver/BallPublisher.h"
#include "scenes/Scene.h"
#include <memory>
#include <vector>

class MainScene : public Scene
{
  public:
	MainScene() = default;
	~MainScene();

	virtual void update() override;
	virtual void render() override;

	virtual void init() override;
	virtual void close() override;

  private:
	void spawnObject(ObjectID id);

	std::unique_ptr<ObjectCreator> factory;

	std::shared_ptr<Board> board;
	std::shared_ptr<Ball> ball;
	std::shared_ptr<ScoreBar> scoreBar;

#pragma region TESTING paddle strategy
	std::vector<std::shared_ptr<Paddle>> paddles;
#pragma endregion
};
