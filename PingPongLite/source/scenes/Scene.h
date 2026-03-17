#pragma once
#include "utils/objectFactory/Creator.h"
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
	std::shared_ptr<Object> createObject(ObjectID object, std::string fileName, std::string& folderPath, int w, int h);

	std::vector<std::shared_ptr<Object>> gameObjects;
	std::unique_ptr<Creator> factory;

	std::string folderPath;
	bool isActive;
};
