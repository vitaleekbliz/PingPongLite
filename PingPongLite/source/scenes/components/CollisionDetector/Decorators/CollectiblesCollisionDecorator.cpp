#include "CollectiblesCollisionDecorator.h"

void CollectiblesCollisionDecorator::addCollectable(std::weak_ptr<Object> item)
{
	collectibles.push_back(item);
}

std::optional<std::weak_ptr<Object>> CollectiblesCollisionDecorator::resolveCollisions(const SDL_FRect& ballCollider)
{
	for (auto it = collectibles.begin(); it != collectibles.end();)
	{
		if (auto shared = it->lock())
		{
			if (checkForObjectCollision(ballCollider, shared))
				return std::make_optional<std::weak_ptr<Object>>(shared);
			it++;
		}
		else
		{
			it = collectibles.erase(it);
		}
	}

	return {};
}
