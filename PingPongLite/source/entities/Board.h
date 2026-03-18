#pragma once
#include "Object.h"

class Board : public Object
{
  public:
	Board();
	virtual void update() override {};
	void render() override;
};
