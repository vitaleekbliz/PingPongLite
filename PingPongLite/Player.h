#pragma once
#include "Object.h"
#include "SDLHandler.h"

class Player : public Object
{
  public:
	Player();
	void update(float deltaTime) override;
	void render() override;

  private:
	void moveBackToBounds();
	void followMouse(float deltaTime);

	void onTextureLoaded() override;

	int offset;
	int speed;
	int maxHeight;
	int minHeight;
};
