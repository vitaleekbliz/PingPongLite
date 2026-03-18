#pragma once
#include "interfaces/textureObserver/TexturePublisher.h"
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

class Object : public TexturePublisher
{
  public:
	Object() = default;
	virtual ~Object() = default;

	virtual void update() = 0;
	virtual void render() = 0;

	void setPosition(SDL_FPoint pos);
	SDL_FPoint getPosition() const;

	void setSize(SDL_FPoint size);
	SDL_FPoint getSize() const;

	SDL_FRect getCollider() const;

  protected:
	virtual void requestDraw(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip,
							 bool isRectCentered = false) override;

	SDL_FPoint size = {0.f, 0.f};
	SDL_FPoint position = {0.f, 0.f};
};
