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

	void setPosition(SDL_FPoint pos);
	SDL_FPoint getPosition();

  protected:
	SDL_FPoint position;
	std::unique_ptr<TextureComponent> textureComponent;
};
