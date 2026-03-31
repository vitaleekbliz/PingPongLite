#pragma once
#include "entities/Object.h"
#include <SDL3/SDL.h>
#include <memory>
#include <optional>
#include <vector>

class CollisionDecorator
{
  public:
	virtual ~CollisionDecorator() = default;

  protected:
	bool checkForObjectCollision(const SDL_FRect& ballCollider, std::weak_ptr<Object> paddle);

  private:
	bool checkCircleInsideBox(const SDL_FRect& ball, const SDL_FRect& rect);
};
