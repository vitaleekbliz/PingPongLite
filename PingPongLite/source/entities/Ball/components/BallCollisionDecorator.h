#pragma once
#include <SDL3/SDL.h>
#include <entities/Object.h>

class BallCollisionDecorator
{
  public:
	void setPaddleReference(std::weak_ptr<Object> paddle);
	SDL_FRect getPaddleCollider();

	bool checkForCollisions(SDL_FPoint* ballPos, SDL_FPoint* ballSize);

  private:
	std::weak_ptr<Object> paddle;
	bool checkCircleInsideBox(SDL_FPoint* pos, SDL_FPoint* size, const SDL_FRect rect);
};
