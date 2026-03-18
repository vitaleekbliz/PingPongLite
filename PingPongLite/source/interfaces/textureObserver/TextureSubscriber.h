#pragma once

enum class TEXTURE : char
{
	BOARD,
	BALL,
	COMPUTER,
	PLAYER,
	SCORE_BAR
};

class TextureSubscriber
{
  public:
	virtual ~TextureSubscriber() = default;
	virtual void onDrawRequest() const = 0;
};