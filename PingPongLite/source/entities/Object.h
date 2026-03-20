#pragma once
#include "interfaces/fontObserver/FontPublisher.h"
#include "interfaces/textureObserver/TexturePublisher.h"
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

class Object : public TexturePublisher, public FontPublisher
{
  public:
	Object() = default;
	virtual ~Object() = default;

	virtual void update() = 0;
	virtual void render() = 0;

	void setPosition(SDL_FPoint pos);
	const SDL_FPoint* getPosition();

	void setSize(SDL_FPoint size);
	const SDL_FPoint* getSize();

	SDL_FRect getCollider() const;

  protected:
	virtual void requestDrawTexture(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip,
									bool isDestinationCentered = false) override;
	virtual void requestDrawText(FONT id, std::string text, SDL_FPoint* position, int size, SDL_Color color) override;

	SDL_FPoint size = {0.f, 0.f};
	SDL_FPoint position = {0.f, 0.f};
};
