#pragma once
#include "core/SDLHandler.h"
#include "entities/Collectibles/subclasses/BlueStar.h"
#include "entities/Collectibles/subclasses/Potion.h"
#include "entities/Collectibles/subclasses/RedStar.h"
#include "entities/Object.h"
#include "entities/interfaces/ChangeScoreObserver/ChangeScorePublisher.h"
#include "entities/interfaces/StrategyObserver/StrategyPublisher.h"
#include "scenes/components/interfaces/CollectiblePickedObserver/CollectiblePickedSubscriber.h"
#include "scenes/components/interfaces/CollectibleSpawnObserver/CollectibleSpawnedPublisher.h"
#include <map>
#include <memory>
#include <random>
#include <vector>

class CollectibleSpawner : public Object,
						   public CollectibleSpawnedPublisher,
						   public CollectiblePickedSubscriber,
						   public ChangeScorePublisher,
						   public StrategyPublisher
{
  public:
	virtual void render() override;
	virtual void update() override;

	virtual void onCollectiblePicked(std::weak_ptr<Object> collectible) override;

  private:
	virtual void notifyCollectibleSpawned(std::weak_ptr<Object> collectible) override;
	virtual void notifyAddScore(int value, bool computer) override;
	virtual void notifyStrategyChange() override;

	void activateCollectible(COLLECTIBLE type);

	void spawnNewCollectible();
	COLLECTIBLE getRandomCollectable();

	std::vector<std::shared_ptr<Collectible>> collectibles;

	const float cooldown = 10.f;
	float timer = cooldown;

	const float spawnOffsetX = 300.f;
	const float spawnOffsetY = 150.f;

	std::mt19937 generator{std::random_device{}()};

	std::map<COLLECTIBLE, int> weights = {
		{COLLECTIBLE::RED_STAR, 50}, {COLLECTIBLE::BLUE_STAR, 50}, {COLLECTIBLE::POTION, 10}};
};
