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

	std::shared_ptr<Object> spawnObject(ObjectID object);

	std::vector<std::shared_ptr<Object>> gameObjects;
	std::unique_ptr<ObjectCreator> factory;

	std::string folderPath;
	bool isActive;

	std::shared_ptr<Object> board;
	std::shared_ptr<Object> computer;
	std::shared_ptr<Object> player;
	std::shared_ptr<Object> ball;
	std::shared_ptr<Object> scoreBar;
};
