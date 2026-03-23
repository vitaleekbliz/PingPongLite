#include "Board.h"

Board::Board()
{
	setPosition({640, 380});
	setSize({1280, 680});
}

void Board::update()
{
	checkBallBoundaries();
}

void Board::render()
{
	SDL_FRect destination = getCollider();
	TextureHandler::get().drawTexture(TEXTURE::BOARD, destination, SDL_FLIP_NONE);
}

void Board::setReference(std::shared_ptr<Ball> ball)
{
	this->ball = ball;
}

void Board::notify(BOUNDARY event)
{
	for (auto it = BoundarySubscribers.begin(); it != BoundarySubscribers.end();)
	{
		if (auto observer = it->lock())
		{
			observer->onBoundaryEvent(event);
			it++;
		}
		else
		{
			it = BoundarySubscribers.erase(it);
		}
	}
}

void Board::checkBallBoundaries()
{
	auto ballLock = ball.lock();

	if (!ballLock)
	{
		return;
	}

	SDL_FPoint pos = ballLock->getPosition();
	SDL_FPoint size = ballLock->getSize();

	// TODO enchance logic to consider this Board::size and position for boundaries calculations
	// instead of hardcoded values
	// Ps. used for calculating dynamic ball size bounces
	float leftBoundary = size.x / 2;
	float rightBoundary = 1280 - size.x / 2;
	float topBoundary = size.y / 2 + 40;
	float bottomBoundary = 720 - size.y / 2;

	if (pos.y < topBoundary)
	{
		ballLock->setPosition({pos.x, topBoundary});
		notify(BOUNDARY::TOP);
	}
	else if (pos.y > bottomBoundary)
	{
		ballLock->setPosition({pos.x, bottomBoundary});
		notify(BOUNDARY::BOTTOM);
	}
	else if (pos.x <= leftBoundary)
	{
		notify(BOUNDARY::LEFT);
	}
	else if (pos.x >= rightBoundary)
	{
		notify(BOUNDARY::RIGHT);
	}
}