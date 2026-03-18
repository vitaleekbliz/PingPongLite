#include "Ball.h"

Ball::Ball()
{
	size.x = 30;
	size.y = 30;

	reset();
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

void Ball::update()
{
	applyMovement();
	bounceTopBottom();
	bounceLeftRight();
	resolvePaddleCollision(playerObject, false);
	resolvePaddleCollision(computerObject, true);

	// TODO remove crutch
	colisionElapsed += SDLHandler::get().getTick();
}

void Ball::render()
{
	SDL_FRect destination = getCollider();
	requestDraw(TEXTURE::BALL, destination, SDL_FLIP_NONE);
}

void Ball::setPlayerReference(std::weak_ptr<Object> player)
{
	playerObject = player;
}

void Ball::setComputerReference(std::weak_ptr<Object> computer)
{
	computerObject = computer;
}

void Ball::reset()
{
	position = {640, (float)SDLHandler::get().WINDOW_HEIGHT / 2};
	setRandomDirection();
	currentSpeed = baseSpeed;
}

void Ball::setRandomDirection()
{
	float& x = direction.x;
	float& y = direction.y;
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
		x = -1;
		y = 0;
	}
}

void Ball::applyMovement()
{
	float deltaTime = SDLHandler::get().getTick();

	position.x += deltaTime * currentSpeed * direction.x;
	position.y += deltaTime * currentSpeed * direction.y;
}

void Ball::bounceTopBottom()
{
	if (position.y <= topBoundary)
	{
		position.y = topBoundary;
		direction.y *= -1.0f;
		notify(BallEvent::WALL_HIT);
	}
	else if (position.y >= bottomBoundary)
	{
		position.y = bottomBoundary;
		direction.y *= -1.0f;
		notify(BallEvent::WALL_HIT);
	}
}

void Ball::bounceLeftRight()
{
	// TODO add notify Logic
	if (position.x <= leftBoundary)
	{
		notify(BallEvent::GOAL_LEFT);
		reset();
	}
	else if (position.x >= rightBoundary)
	{
		notify(BallEvent::GOAL_RIGHT);
		reset();
	}
}

void Ball::resolvePaddleCollision(std::weak_ptr<Object> object, bool forComputer)
{
	if (auto objectLock = object.lock())
	{
		if (checkCollision(objectLock->getCollider()))
		{
			direction.x = forComputer ? std::abs(direction.x) : -std::abs(direction.x);

			accelerateOnImpact();
			notify(BallEvent::PADDLE_HIT);
		}
	}
	else
	{
		static bool warnedOnce = false;
		if (!warnedOnce)
		{
			warnedOnce = true;
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] Player collider is expired or null.", __FUNCTION__);
		}
	}
}

bool Ball::checkCollision(const SDL_FRect rect)
{
	SDL_FPoint start = position;

	SDL_FPoint rectCenter = {rect.x + rect.w / 2, rect.y + rect.h / 2};

	// calculate vector 2d to the center of the square
	SDL_FPoint dirVector = {rectCenter.x - start.x, rectCenter.y - start.y};

	// normalize vector
	float length = sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
	dirVector.x /= length;
	dirVector.y /= length;

	// get end pos of line
	float radius = size.x / 2;

	dirVector.x *= radius;
	dirVector.y *= radius;

	SDL_FPoint end = {start.x + dirVector.x, start.y + dirVector.y};

	// Draw a line to rectangle and get intersaction
	// return checkLineRectIntersection()
	return SDL_GetRectAndLineIntersectionFloat(&rect, &start.x, &start.y, &end.x, &end.y);
}

void Ball::accelerateOnImpact()
{
	// TODO remove crutch cooldown for accelaration
	// start
	if (colisionElapsed < 0.2)
		return;
	colisionElapsed = 0.f;
	// end
	currentSpeed *= speedMultiplier;
	if (currentSpeed > maxSpeed)
		currentSpeed = maxSpeed;
}
