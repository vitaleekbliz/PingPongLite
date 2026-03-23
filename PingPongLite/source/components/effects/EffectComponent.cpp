#include "EffectComponent.h"

EffectComponent::EffectComponent()
{
	setSize({36, 48});
	state = OFF;
}

void EffectComponent::update()
{
	if (state == OFF)
		return;

	if (currentDuration > maxDuration)
	{
		currentDuration = 0.f;
		currentFrame = 0;
		state = END;
	}

	switchFrame();
}

void EffectComponent::render()
{
	if (state != OFF)
		draw();
}

void EffectComponent::start(bool color, float duration)
{
	if (state == OFF || state == END)
		state = START;
	this->color = color;
	maxDuration = duration;
	currentDuration = 0.f;
	currentFrame = 0;
}

void EffectComponent::upgradeColor(bool color)
{
	this->color = color;
}

void EffectComponent::draw()
{
	EFFECT sprite = getSprite();

	SDL_FRect source = SDL_FRect();
	source.x = 24 * currentFrame;
	source.w = 24;
	source.h = 32;

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

	frameTime += deltaTime;
	currentDuration += deltaTime;

	if (frameTime < frameThreshold)
	{
		return;
	}

	// Switch to next frame
	frameTime = 0.f;
	currentFrame++;

	if (state == START && currentFrame >= startFrames)
	{
		state = LOOP;
		currentFrame = 0;
	}
	else if (state == LOOP && currentFrame >= loopFrames)
	{
		currentFrame = 0;
	}
	else if (state == END && currentFrame >= endFrames)
	{
		state = OFF;
	}
}
