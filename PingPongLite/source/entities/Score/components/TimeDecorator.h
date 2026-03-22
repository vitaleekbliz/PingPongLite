#pragma once
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/FontHandler.h"
#include "core/subsystems/TextureHandler.h"
#include "entities/Object.h"

class TimeDecorator : public Object
{
  public:
	virtual void update() override;
	virtual void render() override;

  private:
	SDL_Color color = SDL_Color(211, 211, 211);

	float seconds = 0;
	int minutes = 0;
};