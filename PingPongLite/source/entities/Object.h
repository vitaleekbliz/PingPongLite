#pragma once
#include "components/TextureComponent.h"
#include <SDL3/SDL.h>
#include <memory>
#include <utility>

enum class ObjectID : char
{
	BALL,
	COMPUTER,
	PLAYER,
	SCORE_BAR,
	BOARD
};

class Object
{
  public:
	Object();
	virtual ~Object() = default;

	virtual void update() = 0;
	virtual void render() = 0;

	void setPosition(std::pair<float, float> pos);
	std::pair<float, float> getPosition();

  protected:
	std::pair<float, float> position;
	std::unique_ptr<TextureComponent> textureComponent;
};
