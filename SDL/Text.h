#pragma once

#include "Game.h"
#include <SDL_ttf.h>

class Text {
public:
	Text(const std::string& font_path, int font_size, const std::string& text, const SDL_Color& color);

	void Render(int x, int y) const;

	static SDL_Texture* loadFont(const std::string& font_path, int font_size, const std::string& text, const SDL_Color& color);

private:
	SDL_Texture* _text_texture = nullptr;
	mutable SDL_Rect textRect;
};