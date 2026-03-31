#pragma once
#include "entities/Collectibles/Collectible.h"

class RedStar : public Collectible
{
  public:
	RedStar();
	virtual void render() override;
};
