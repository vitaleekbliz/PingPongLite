#pragma once
#include "entities/Object.h"
#include "core/subsystems/TextureHandler.h"

class Board : public Object
{
  public:
	Board();
	virtual void update() override;
	virtual void render() override;
};
