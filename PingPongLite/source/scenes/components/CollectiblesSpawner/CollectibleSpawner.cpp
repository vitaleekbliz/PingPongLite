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

void CollectibleSpawner::onCollectiblePicked(std::weak_ptr<Object> collectible)
{
	auto pickedObject = collectible.lock();
	if (!pickedObject)
	{
		SDL_Log("Collectible spawner received invalid picked collectible!\n");
		return;
	}
	auto it = std::find(collectibles.begin(), collectibles.end(), pickedObject);

	if (it != collectibles.end())
	{
		activateCollectible((*it)->getType());

		collectibles.erase(it);
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

void CollectibleSpawner::notifyAddScore(int value, bool computer)
{
	for (auto it = changeScoreSubscribers.begin(); it != changeScoreSubscribers.end();)
	{
		if (auto shared = it->lock())
		{
			shared->onAddScore(value, computer);
			it++;
		}
		else
		{
			it = changeScoreSubscribers.erase(it);
		}
	}
}

void CollectibleSpawner::notifyStrategyChange()
{
	for (auto it = strategySubscribers.begin(); it != strategySubscribers.end();)
	{
		if (auto subscriber = it->lock())
		{
			subscriber->onStrategyChange();
			it++;
		}
		else
		{
			it = strategySubscribers.erase(it);
		}
	}
}

void CollectibleSpawner::activateCollectible(COLLECTIBLE type)
{
	switch (type)
	{
	case COLLECTIBLE::BLUE_STAR:
		notifyAddScore(1, true);
		break;
	case COLLECTIBLE::RED_STAR:
		notifyAddScore(1, false);
		break;
	case COLLECTIBLE::POTION:
		notifyStrategyChange();
		break;
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
