#pragma once
#include "core/SDLHandler.h"
#include "entities/Collectibles/subclasses/BlueStar.h"
#include "entities/Collectibles/subclasses/Potion.h"
#include "entities/Collectibles/subclasses/RedStar.h"
#include "entities/Object.h"
#include "scenes/components/interfaces/CollectibleSpawnObserver/CollectibleSpawnedPublisher.h"
#include <map>
#include <memory>
#include <random>
#include <vector>

class CollectibleSpawner : public Object, public CollectibleSpawnedPublisher
{
  public:
	virtual void render() override;
	virtual void update() override;

  private:
	virtual void notifyCollectibleSpawned(std::weak_ptr<Object> collectible) override;

	void spawnNewCollectible();
	COLLECTIBLE getRandomCollectable();

	std::vector<std::shared_ptr<Collectible>> collectibles;

	const float cooldown = 0.01;
	float timer = cooldown;

	const float spawnOffsetX = 300.f;
	const float spawnOffsetY = 150.f;

	std::mt19937 generator{std::random_device{}()};

	std::map<COLLECTIBLE, int> weights = {
		{COLLECTIBLE::RED_STAR, 50}, {COLLECTIBLE::BLUE_STAR, 50}, {COLLECTIBLE::POTION, 10}};
};
