#include "CollectiblesCollisionDecorator.h"

void CollectiblesCollisionDecorator::addCollectable(std::weak_ptr<Object> item)
{
	collectibles.push_back(item);
}

std::vector<std::weak_ptr<Object>> CollectiblesCollisionDecorator::resolveCollisions(const SDL_FRect& ballCollider)
{
	std::vector<std::weak_ptr<Object>> pickedCollectibles;
	for (auto it = collectibles.begin(); it != collectibles.end();)
	{
		if (auto shared = it->lock())
		{
			if (checkForObjectCollision(ballCollider, shared))
				pickedCollectibles.push_back(shared);
			it++;
		}
		else
		{
			it = collectibles.erase(it);
		}
	}

	return pickedCollectibles;
}
