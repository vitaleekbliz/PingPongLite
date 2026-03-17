#pragma once
#include "Object.h"
#include "SDLHandler.h"

class Player : public Object
{
  public:
	Player();
	void update() override;
	void render() override;

  private:
	void keepInBounds();
	void followMouse();

	void onTextureLoaded() override;

	int offset;
	int speed;
	int maxHeight;
	int minHeight;
};
