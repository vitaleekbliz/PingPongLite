#include "Ball.h"

Ball::Ball()
{
	setupTexture();
	resetPos();
	setRandomDirection();
	initVariables();
}

void Ball::notify(BallEvent event)
{
	for (auto it = subscribers.begin(); it != subscribers.end();)
	{
		if (auto observer = it->lock())
		{
			observer->onBallEvent(event);
			it++;
		}
		else
		{
			it = subscribers.erase(it);
		}
	}
}

void Ball::initVariables()
{
	int halfHeight = height / 2;
	int halfWidth = width / 2;
	leftBoundary = 40 + halfHeight;
	rightBoundary = SDLHandler::get().WINDOW_HEIGHT - halfHeight;
	topBoundary = halfWidth;
	bottomBoundary = SDLHandler::get().WINDOW_WIDTH - halfWidth;
}

void Ball::setupTexture()
{

	textureComponent->setMetaData(textureName, width, height);
	textureComponent->loadMedia();
}

void Ball::drawBall()
{
	SDL_FRect destination = SDL_FRect();
	destination.x = position.first;
	destination.y = position.second;
	destination.h = height;
	destination.w = width;

	textureComponent->draw(destination, SDL_FLIP_NONE);
}

Ball::~Ball()
{
}

void Ball::update()
{
	applyMovement();
	checkBoundaries();
}

void Ball::render()
{
	drawBall();
}

void Ball::resetPos()
{
	position = {SDLHandler::get().WINDOW_WIDTH / 2, SDLHandler::get().WINDOW_HEIGHT / 2};
}

void Ball::setRandomDirection()
{
	float& x = direction.first;
	float& y = direction.second;
	x = (std::rand() % 3) / 1.f - 1.f;
	y = (std::rand() % 3) / 1.f - 1.f;

	// Fixed length < 0 bug
	if (std::abs(x) < 0.5f)
	{
		x = (x < 0) ? -0.5f : 0.5f;
	}

	float length = std::sqrt(x * x + y * y);

	if (length > 0.0f)
	{
		x /= length;
		y /= length;
	}
	else
	{

		// TODO
		//  BUG: priority LOW: length of vector is 0 -> vector is NOT normalized; possible solution: generate direction
		//  with minimal value
		// Crutch (Emergency fallback) : just launch the ball to the computer
		x = -1;
		y = 0;
	}
}

void Ball::applyMovement()
{
	float deltaTime = SDLHandler::get().getTick();

	position.first += deltaTime * speed * direction.first;
	position.second += deltaTime * speed * direction.second;
}

void Ball::checkBoundaries()
{
	bounceTopBottom();
	bounceLeftRight();
}

void Ball::bounceTopBottom()
{
	if (position.second <= leftBoundary)
	{
		position.second = leftBoundary;
		direction.second *= -1.0f;
	}
	else if (position.second >= rightBoundary)
	{
		position.second = rightBoundary;
		direction.second *= -1.0f;
	}
}

void Ball::bounceLeftRight()
{
	// TODO add notify Logic
	if (position.first <= topBoundary)
	{
		notify(BallEvent::GOAL_LEFT);
		resetPos();
		setRandomDirection();
	}
	else if (position.first >= bottomBoundary)
	{
		notify(BallEvent::GOAL_RIGHT);
		resetPos();
		setRandomDirection();
	}
}
