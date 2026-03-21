#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <utility>

enum class ObjectID : char
{
	BALL,
	SCORE_BAR,
	BOARD,
	PADDLE
};

class Object
{
  public:
	Object() = default;
	virtual ~Object() = default;

	virtual void update() = 0;
	virtual void render() = 0;

	void setPosition(SDL_FPoint pos);
	SDL_FPoint getPosition();

	void setSize(SDL_FPoint size);
	SDL_FPoint getSize();

	SDL_FRect getCollider() const;

  protected:
	SDL_FPoint size = {0.f, 0.f};
	SDL_FPoint position = {0.f, 0.f};
};
