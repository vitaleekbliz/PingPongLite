#include "TextureHandler.h"

void TextureHandler::init()
{
	SDL_Renderer* renderer = SDLHandler::get().getRenderer();

	board = load("Board.png", renderer);
	ball = load("Ball.png", renderer);
	computer = load("Computer.png", renderer);
	player = load("Player.png", renderer);
	scoreBar = load("ScoreBar.png", renderer);
}

void TextureHandler::close()
{
	if (board)
		SDL_DestroyTexture(board);
	if (ball)
		SDL_DestroyTexture(ball);
	if (computer)
		SDL_DestroyTexture(computer);
	if (player)
		SDL_DestroyTexture(player);
	if (scoreBar)
		SDL_DestroyTexture(scoreBar);
}

void TextureHandler::onDrawRequest(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip, bool isRectCentered) const
{
	SDL_Renderer* renderer = SDLHandler::get().getRenderer();

	// center picture
	if (isRectCentered)
	{
		destination.x -= destination.w / 2;
		destination.y -= destination.h / 2;
	}

	switch (texture)
	{
	case TEXTURE::BOARD:
		SDL_RenderTextureRotated(renderer, board, NULL, &destination, 0, NULL, flip);
		break;
	case TEXTURE::BALL:
		SDL_RenderTextureRotated(renderer, ball, NULL, &destination, 0, NULL, flip);
		break;
	case TEXTURE::COMPUTER:
		SDL_RenderTextureRotated(renderer, computer, NULL, &destination, 0, NULL, flip);
		break;
	case TEXTURE::PLAYER:
		SDL_RenderTextureRotated(renderer, player, NULL, &destination, 0, NULL, flip);
		break;
	case TEXTURE::SCORE_BAR:
		SDL_RenderTextureRotated(renderer, scoreBar, NULL, &destination, 0, NULL, flip);
		break;
	default:
		break;
	}
}

SDL_Texture* TextureHandler::load(std::string fileName, SDL_Renderer* renderer) const
{
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
