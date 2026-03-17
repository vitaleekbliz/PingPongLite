#pragma once
#include "utils/objectFactory/objectCreator.h"
#include <memory>
#include <vector>

class Scene
{
  public:
	Scene();
	~Scene();

	void update();
	void render();

	void init();
	bool isRunning() const;
	void close();

  private:
	void populateScene();
	void setupInterfaces();
	void setupComputerToBallRef();
	void setupBallListeners();

	std::shared_ptr<Object> spawnObject(ObjectID object);
	void destroyObject(std::shared_ptr<Object> object);

	std::vector<std::shared_ptr<Object>> gameObjects;
	std::unique_ptr<ObjectCreator> factory;

	bool isActive;

	std::weak_ptr<Object> board;
	std::weak_ptr<Object> computer;
	std::weak_ptr<Object> player;
	std::weak_ptr<Object> ball;
	std::weak_ptr<Object> scoreBar;
};
