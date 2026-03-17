#pragma once
#include "Creator.h"
#include <memory>
#include <vector>

class Scene
{
  public:
	Scene();
	~Scene();

	void update(float deltaTime);
	void render();

	void init();
	bool isRunning();
	void close();

  private:
	std::shared_ptr<Object> createObject(ObjectID object, std::string fileName, std::string& folderPath, int w, int h);

	std::vector<std::shared_ptr<Object>> gameObjects;
	std::unique_ptr<Creator> factory;

	std::string folderPath;
	bool isActive;
};
