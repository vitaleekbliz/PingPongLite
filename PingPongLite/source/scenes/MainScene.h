#pragma once
#include "core/AudioHandler.h"
#include "scenes/Scene.h"
#include "utils/objectFactory/objectCreator.h"
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
#pragma region MainScene::init() refactoring
	void populateScene(ObjectID id);
	void setupBallObserver();
	void setupTextureObserver();
#pragma endregion

	std::unique_ptr<ObjectCreator> factory;
	std::shared_ptr<AudioHandler> audioHandler;
	std::shared_ptr<TextureHandler> textureHandler;

	std::shared_ptr<Board> board;
	std::shared_ptr<Computer> computer;
	std::shared_ptr<Player> player;
	std::shared_ptr<Ball> ball;
	std::shared_ptr<ScoreBar> scoreBar;
};
