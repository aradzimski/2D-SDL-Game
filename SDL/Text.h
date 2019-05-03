#pragma once

#include "Game.h"
#include <SDL_ttf.h>

class Text {
public:
	Text(const std::string& font_path, int font_size, const std::string& text, const SDL_Color& color);
	~Text();

	void Render(int x, int y);

	SDL_Texture* loadFont(const std::string& font_path, int font_size, const std::string& text, const SDL_Color& color);

private:
	TTF_Font* font;
	SDL_Texture* _text_texture = nullptr;
	SDL_Rect textRect;
	SDL_Surface* text_surface;
	SDL_Texture* text_texture;
};