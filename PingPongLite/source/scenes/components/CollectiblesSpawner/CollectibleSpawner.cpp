#include "CollectibleSpawner.h"

void CollectibleSpawner::render()
{
	for (auto it = collectibles.begin(); it != collectibles.end(); it++)
	{
		(*it)->render();
	}
}

void CollectibleSpawner::update()
{
	timer -= SDLHandler::get().getTick();

	if (timer < 0.f)
	{
		timer = cooldown;
		spawnNewCollectible();
	}
}

void CollectibleSpawner::notifyCollectibleSpawned(std::weak_ptr<Object> collectible)
{
	for (auto it = collectibleSpawnSubscribers.begin(); it != collectibleSpawnSubscribers.end();)
	{
		if (auto shared = it->lock())
		{
			shared->onCollectibleSpawned(collectible);
			it++;
		}
		else
		{
			it = collectibleSpawnSubscribers.erase(it);
		}
	}
}

void CollectibleSpawner::spawnNewCollectible()
{
	COLLECTIBLE random = getRandomCollectable();
	switch (random)
	{
	case COLLECTIBLE::BLUE_STAR:
		collectibles.push_back(std::make_shared<BlueStar>());
		break;
	case COLLECTIBLE::RED_STAR:
		collectibles.push_back(std::make_shared<RedStar>());
		break;
	case COLLECTIBLE::POTION:
		collectibles.push_back(std::make_shared<Potion>());
		break;
	}

	// set random postion with offset
	std::uniform_real_distribution<float> distX(position.x - spawnOffsetX, position.x + spawnOffsetX);
	std::uniform_real_distribution<float> distY(position.y - spawnOffsetY, position.y + spawnOffsetY);

	collectibles.back()->setPosition({distX(generator), distY(generator)});

	notifyCollectibleSpawned(collectibles.back());
}

COLLECTIBLE CollectibleSpawner::getRandomCollectable()
{
	std::vector<int> weightsVector;

	for (const auto& [item, weight] : weights)
	{
		weightsVector.push_back(weight);
	}

	std::discrete_distribution<int> dist{weightsVector.begin(), weightsVector.end()};
	COLLECTIBLE randItem = static_cast<COLLECTIBLE>(dist(generator));
	return randItem;
}
