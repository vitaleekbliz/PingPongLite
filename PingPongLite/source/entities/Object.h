#pragma once
#include "interfaces/fontObserver/FontPublisher.h"
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

class Object : public TexturePublisher, public FontPublisher
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
	virtual void requestDrawTexture(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip,
									bool isRectCentered = false) override;
	virtual void requestDrawText(SDL_FPoint* position, int size, FONT id, std::string text, SDL_Color color) override;

	SDL_FPoint size = {0.f, 0.f};
	SDL_FPoint position = {0.f, 0.f};
};
