#include "Text.h"

Text::Text(const std::string& font_path, int font_size, const std::string& text, const SDL_Color& color)
{
	_text_texture = loadFont(font_path, font_size, text, color);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &textRect.w, &textRect.h);
}

Text::~Text()
{
	SDL_DestroyTexture(text_texture);
	SDL_DestroyTexture(_text_texture);
}

void Text::Render(int x, int y)
{
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(Game::renderer, _text_texture, nullptr, &textRect);
}

SDL_Texture* Text::loadFont(const std::string& font_path, int font_size, const std::string& text, const SDL_Color& color)
{
	font = TTF_OpenFont(font_path.c_str(), font_size);
	text_surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
	text_texture = SDL_CreateTextureFromSurface(Game::renderer, text_surface);

	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);

	return text_texture;
}
