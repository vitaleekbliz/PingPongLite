#pragma once
#include "components/objectFactory/Creator.h"
#include "core/AudioHandler.h"
#include "core/FontHandler.h"
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

	void linkBallObserver(std::shared_ptr<BallSubscriber> subscriber, std::shared_ptr<BallPublisher> publisher);
	void linkTextureObserver(std::shared_ptr<TextureSubscriber> subscriber,
							 std::shared_ptr<TexturePublisher> publisher);
	void linkFontObserver(std::shared_ptr<FontSubscriber> subscriber, std::shared_ptr<FontPublisher> publisher);

	std::unique_ptr<ObjectCreator> factory;
	std::shared_ptr<AudioHandler> audioHandler;
	std::shared_ptr<TextureHandler> textureHandler;
	std::shared_ptr<FontHandler> fontHandler;

	std::shared_ptr<Board> board;
	std::shared_ptr<Ball> ball;
	std::shared_ptr<ScoreBar> scoreBar;

#pragma region TESTING paddle strategy
	std::vector<std::shared_ptr<Paddle>> paddles;
#pragma endregion
};
