#include "TextureHandler.h"

TextureHandler::~TextureHandler()
{
	close();
}

TextureHandler& TextureHandler::get()
{
	static TextureHandler instance;
	return instance;
}

void TextureHandler::init()
{
	board = loadTexture("Board.png");
	ball = loadTexture("Ball.png");
	computer = loadTexture("Computer.png");
	player = loadTexture("Player.png");
	scoreBar = loadTexture("ScoreBar.png");
}

void TextureHandler::close()
{
	SDL_DestroyTexture(board);
	SDL_DestroyTexture(ball);
	SDL_DestroyTexture(computer);
	SDL_DestroyTexture(player);
	SDL_DestroyTexture(scoreBar);
}

void TextureHandler::drawTexture(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip, bool isWorldPosition)
{
	SDL_Renderer* renderer = SDLHandler::get().getRenderer();

	if (isWorldPosition)
	{
		destination.x -= destination.w / 2;
		destination.y -= destination.h / 2;
	}

	SDL_RenderTextureRotated(renderer, getLoadedTexture(texture), NULL, &destination, 0, NULL, flip);
}

SDL_Texture* TextureHandler::loadTexture(std::string fileName)
{
	SDL_Renderer* renderer = SDLHandler::get().getRenderer();

	std::string basePath = SDL_GetBasePath();
	std::string fullPath = basePath + audioAssetFolder + fileName;

	SDL_Surface* surface;
	surface = SDL_LoadPNG(fullPath.c_str());
	if (!surface)
	{
		SDL_Log("Couldn't load %s: %s", fullPath.c_str(), SDL_GetError());
		return NULL;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	if (!texture)
	{
		SDL_Log("Couldn't create texture from surface: %s", SDL_GetError());
		return NULL;
	}

	return texture;
}

SDL_Texture* TextureHandler::getLoadedTexture(TEXTURE texture)
{
	switch (texture)
	{
	case TEXTURE::BOARD:
		return board;
		break;
	case TEXTURE::BALL:
		return ball;
		break;
	case TEXTURE::COMPUTER:
		return computer;
		break;
	case TEXTURE::PLAYER:
		return player;
		break;
	case TEXTURE::SCORE_BAR:
		return scoreBar;
		break;
	default:
		break;
	}
}
