#pragma once
#include "core/AudioHandler.h"
#include "utils/objectFactory/objectCreator.h"
#include <memory>
#include <vector>

class MainScene
{
  public:
	MainScene();
	~MainScene();

	void update();
	void render();

	void init();
	bool isRunning() const;
	void close();

  private:
	void spawnEntities();
	void bindDependencies();
	void bindBallToComputer();
	void registerBallObservers();
	void resolvePaddleReferences();

	void handlerCollisions();

	std::shared_ptr<Object> spawnObject(ObjectID object);
	void destroyObject(std::shared_ptr<Object> object);

	std::vector<std::shared_ptr<Object>> gameObjects;
	std::unique_ptr<ObjectCreator> factory;
	std::shared_ptr<AudioHandler> audioHandler;

	bool isActive;

	std::shared_ptr<Board> board;
	std::shared_ptr<Computer> computer;
	std::shared_ptr<Player> player;
	std::shared_ptr<Ball> ball;
	std::shared_ptr<ScoreBar> scoreBar;
};
