#include "Creator.h"

std::shared_ptr<Object> ObjectCreator::create(ObjectID id)
{
	switch (id)
	{
	case ObjectID::BALL:
		return std::make_shared<Ball>();
		break;
	case ObjectID::COMPUTER:
		return std::make_shared<Computer>();
		break;
	case ObjectID::PLAYER:
		return std::make_shared<Player>();
		break;
	case ObjectID::SCORE_BAR:
		return std::make_shared<ScoreBar>();
		break;
	case ObjectID::BOARD:
		return std::make_shared<Board>();
		break;
	case ObjectID::PADDLE:
		return std::make_shared<Paddle>();
	default:
		break;
	}

	return nullptr;
}
