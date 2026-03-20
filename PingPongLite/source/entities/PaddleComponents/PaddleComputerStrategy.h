#pragma once
#include "PaddleStrategy.h"

class PaddleComputerStrategy : public PaddleStrategy
{
  public:
	virtual void track(SDL_FPoint* ownerPos) override;
};
