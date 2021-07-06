#include "Fontsheet.h"
#include "Settings.h"

sf::Sprite* Fontsheet::getSprite(char c){
	int index = c - 'a';
	index = index % settings::FONT_SIZE;
	index = (index < 0) ? 0 : index;
	return font[index].getCurrentSprite();
}

void Fontsheet::startFadeIn(){
	for (int i = 0; i < settings::FONT_SIZE; i++) {
		font[i].m_backwards = true;
		font[i].setSpeed(font[i].getSize()-1, 0.2f);
		font[i].setSpeed(0, -1.0f);		
	}
}

void Fontsheet::startFadeOut(){	
	for (int i = 0; i < settings::FONT_SIZE; i++) {
		font[i].m_backwards = false;
		font[i].setSpeed(font[i].getSize()-1, -1.0f);
		font[i].setSpeed(0, 0.2f);
	}
}

void Fontsheet::update(int i, float delta){
	int index = i - 'a';
	index = index % settings::FONT_SIZE;
	index = (index < 0) ? 0 : index;
	font[index].update(delta);
}
