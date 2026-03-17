#include "Ball.h"

Ball::Ball()
{
	reset();

	// TODO
	// BUG height of texture is not inited
	//--start
	minHeight = 40 + 15; // ScoreBar + ballTextureHeight/2
	maxHeight = SDLHandler::get().WINDOW_HEIGHT - /*height / 2*/ 15;
	minWidth = 0;
	maxWidth = 10000;
	//--end
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

void Ball::onTextureLoaded()
{
	int halfHeight = height / 2;
	int halfWidth = width / 2;
	minHeight = 40 + halfHeight; // ScoreBar + ballTextureHeight/2
	maxHeight = SDLHandler::get().WINDOW_HEIGHT - halfHeight;
	minWidth = halfWidth;
	maxWidth = SDLHandler::get().WINDOW_WIDTH - halfWidth;
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
	auto renderer = SDLHandler::get().getRenderer();

	SDL_FRect destination = SDL_FRect();
	destination.x = position.first - width / 2;
	destination.y = position.second - height / 2;

	destination.h = height;
	destination.w = width;
	SDL_RenderTexture(renderer, texture, NULL, &destination);
}

void Ball::reset()
{
	position = {SDLHandler::get().WINDOW_WIDTH / 2, SDLHandler::get().WINDOW_HEIGHT / 2};
	setRandomDirection();
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
	if (position.second <= minHeight)
	{
		position.second = minHeight;
		direction.second *= -1.0f;
	}
	else if (position.second >= maxHeight)
	{
		position.second = maxHeight;
		direction.second *= -1.0f;
	}
}

void Ball::bounceLeftRight()
{
	// TODO add notify Logic
	if (position.first <= minWidth)
	{
		notify(BallEvent::GOAL_LEFT);
		reset();
	}
	else if (position.first >= maxWidth)
	{
		notify(BallEvent::GOAL_RIGHT);
		reset();
	}
}
