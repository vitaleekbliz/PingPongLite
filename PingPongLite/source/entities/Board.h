#pragma once
#include "Object.h"

class Board : public Object
{
  public:
	Board();
	~Board();
	void update() override;
	void render() override;

  private:
	void drawBoard();

	const int topDrawOffset = 40;
	const std::string textureName = "Board.png";
	const int width = 1280;
	const int height = 720;
};
