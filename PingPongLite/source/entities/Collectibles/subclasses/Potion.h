#pragma once
#include "entities/Collectibles/Collectible.h"

class Potion : public Collectible
{
  public:
	Potion();
	virtual void render() override;
};
