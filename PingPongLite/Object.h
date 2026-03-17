#pragma once
#include "SDL3/SDL.h"
#include "Texture.h"
#include <utility>

enum class ObjectID : char
{
	BALL,
	COMPUTER,
	PLAYER,
	SCORE_BAR,
	BOARD
};

class Object : public Texture
{
  public:
	Object();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual ~Object() = default;

	void setPosition(std::pair<float, float> pos);
	std::pair<float, float> getPosition();

  protected:
	std::pair<float, float> position;
};
