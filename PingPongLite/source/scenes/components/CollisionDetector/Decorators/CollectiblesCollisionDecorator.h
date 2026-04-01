#pragma once
#include "CollisionDecorator.h"

class CollectiblesCollisionDecorator : public CollisionDecorator
{
  public:
	void addCollectable(std::weak_ptr<Object> item);
	std::vector<std::weak_ptr<Object>> resolveCollisions(const SDL_FRect& ballCollider);

  private:
	std::vector<std::weak_ptr<Object>> collectibles;
};
