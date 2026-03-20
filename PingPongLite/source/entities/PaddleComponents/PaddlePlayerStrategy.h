#pragma once
#include "PaddleStrategy.h"

class PaddlePlayerStrategy : public PaddleStrategy
{
  public:
	virtual void track(SDL_FPoint* ownerPos) override;
};
