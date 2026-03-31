#pragma once
#include "core/subsystems/TextureHandler.h"
#include "entities/Object.h"

enum class COLLECTIBLE : char
{
	BLUE_STAR,
	RED_STAR,
	POTION
};

class Collectible : public Object
{
  public:
	Collectible();
	virtual ~Collectible() = default;
	virtual void render() override = 0;
	virtual void update() override {};

	COLLECTIBLE getType() const;

  protected:
	COLLECTIBLE type = COLLECTIBLE::BLUE_STAR;
};
