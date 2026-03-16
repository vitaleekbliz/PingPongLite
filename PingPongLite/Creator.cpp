#include "Creator.h"

std::unique_ptr<Object> Creator::create(ObjectID id)
{
	switch (id)
	{
	case ObjectID::BALL:
		return std::make_unique<Ball>();
		break;
	case ObjectID::PADDLE:
		return std::make_unique<Paddle>();
		break;
	case ObjectID::SCORE_BAR:
		return std::make_unique<ScoreBar>();
		break;
	case ObjectID::BOARD:
		return std::make_unique<Board>();
		break;
	default:
		break;
	}

	return nullptr;
}
