#pragma once
#include "entities/Ball.h"
#include "entities/Board.h"
#include "entities/Computer.h"
#include "entities/Object.h"
#include "entities/Paddle.h"
#include "entities/Player.h"
#include "entities/ScoreBar.h"
#include <memory>

class ObjectCreator
{
  public:
	std::shared_ptr<Object> create(ObjectID id);

  private:
};
