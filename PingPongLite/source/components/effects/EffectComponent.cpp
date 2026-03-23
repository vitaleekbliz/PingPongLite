#include "EffectComponent.h"

EffectComponent::EffectComponent()
{
	setSize({32, 32});
	state = OFF;
}

void EffectComponent::update()
{
	if (state == OFF)
		return;

	if (currentDuration > maxDuration)
		state = END;

	switchFrame();
}

void EffectComponent::render()
{
	// draw();
}

void EffectComponent::start(bool color, float duration)
{
	state = START;
	this->color = color;
	maxDuration = duration;
}

void EffectComponent::draw()
{
	EFFECT sprite = getSprite();

	SDL_FRect source = SDL_FRect();
	source.x = size.x * currentFrame;
	source.w = size.x;
	source.h = size.y;

	EffectHandler::get().drawEffect(sprite, source, getCollider(), SDL_FLIP_NONE);
}

EFFECT EffectComponent::getSprite()
{
	if (color)
		switch (state)
		{
		case START:
			return EFFECT::RED_START;
		case LOOP:
			return EFFECT::RED_LOOP;
		case END:
			return EFFECT::RED_END;
		}
	else
	{
		switch (state)
		{
		case START:
			return EFFECT::BLUE_START;
		case LOOP:
			return EFFECT::BLUE_LOOP;
		case END:
			return EFFECT::BLUE_END;
		}
	}
}

void EffectComponent::switchFrame()
{
	float deltaTime = SDLHandler::get().getTick();

	frameTime += deltaTime * playSpeed;
	currentDuration += deltaTime * playSpeed;

	if (frameTime < frameThreshold)
	{
		return;
	}

	// Switch to next frame
	frameTime = 0.f;
	currentFrame++;

	if (state == START && currentFrame > startFrames)
	{
		state = LOOP;
		currentFrame = 0;
	}
	else if (state == LOOP && currentFrame > loopFrames)
	{
		currentFrame = 0;
	}
	else if (state == END && currentFrame > endFrames)
	{
		state = OFF;
	}
}
