#pragma once
#include <SFML\Graphics.hpp>
#include "Spritesheet.h"
class Fontsheet {
private:
	Spritesheet font[settings::FONT_SIZE];
public:
	int spritesize = 8;
	sf::Sprite* getSprite(char c);
	Fontsheet(){}

	void startFadeIn();
	void startFadeOut();

	void setSpritesheet(Spritesheet sheet[settings::FONT_SIZE]) {
		for (int i = 0; i < settings::FONT_SIZE; i++) {
			font[i] = sheet[i];
		}
	}

	void update(int i, float delta);
};