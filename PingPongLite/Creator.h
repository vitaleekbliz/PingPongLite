#pragma once
#include "Ball.h"
#include "Board.h"
#include "Computer.h"
#include "Object.h"
#include "Player.h"
#include "ScoreBar.h"
#include <memory>

class Creator
{
  public:
	std::shared_ptr<Object> create(ObjectID id);

  private:
};
