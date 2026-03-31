#pragma once
#include "entities/Collectibles/Collectible.h"

class BlueStar : public Collectible
{
  public:
	BlueStar();
	virtual void render() override;
};
