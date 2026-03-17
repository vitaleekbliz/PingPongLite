#include "Ball.h"

Ball::Ball()
{
	resetPos();

	// TODO
	// BUG height of texture is not inited
	minHeight = 40 - 15; // ScoreBar + ballTextureHeight/2
	maxHeight = SDLHandler::get().WINDOW_HEIGHT - /*height / 2*/ 15;
	minWidth;
	maxWidth;
}

void Ball::onTextureLoaded()
{
	int halfHeight = height / 2;
	minHeight = 40 + halfHeight; // ScoreBar + ballTextureHeight/2
	maxHeight = SDLHandler::get().WINDOW_HEIGHT - halfHeight;
}

Ball::~Ball()
{
}

void Ball::update()
{
	//--start--TEMP
	static float sum = 0;
	sum += SDLHandler::get().getTick();
	if (sum > 1)
	{
		resetPos();
		sum = 0;
	}
	//--end--

	applyMovement();
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

void Ball::resetPos()
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

	// TODO
	//  score and reset ball when boundaries reacheched left/right

	// if (position.first <= minWidth)
	//{
	//	notifyScore(GameEvent::RIGHT_SCORE);
	//	resetBall(); // Bring ball back to center
	// }
	// else if (position.first >= maxWidth)
	//{
	//	notifyScore(GameEvent::LEFT_SCORE);
	//	resetBall();
	// }
}

void Ball::bounceTopBottom()
{
	if (position.second <= minHeight)
	{
		position.second = minHeight; // Snap to boundary to prevent getting stuck
		direction.second *= -1.0f;
	}
	else if (position.second >= maxHeight)
	{
		position.second = maxHeight;
		direction.second *= -1.0f;
	}
}
