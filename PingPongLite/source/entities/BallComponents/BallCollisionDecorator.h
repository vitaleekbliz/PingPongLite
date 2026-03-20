#pragma once
#include <SDL3/SDL.h>
#include <entities/Object.h>

enum class COLLITION : char
{
	PLAYER,
	COMPUTER,
	NONE
};

class BallCollisionDecorator
{
  public:
	void setPlayerReference(std::weak_ptr<Object> player);
	void setComputerReference(std::weak_ptr<Object> computer);

  protected:
	COLLITION checkForCollisions(SDL_FPoint* ballPos, SDL_FPoint* ballSize, SDL_FRect& colidingWith);

	bool isCollidingPaddle = false;

  private:
	bool checkCircleInsideBox(SDL_FPoint* pos, SDL_FPoint* size, const SDL_FRect rect);

	std::weak_ptr<Object> playerObject;
	std::weak_ptr<Object> computerObject;
};
