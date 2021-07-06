#pragma once
#include <SFML/Graphics.hpp>
#include "ASCIISymbol.h"
#include "World.h"
#include "Pos2D.h"
#include "Path.h"
class Actor {
public: 
	Actor();
	Actor(Pos2D pos) : symbol_(ASCIISymbol(ASCII::face,sf::Color::Red)), pos_(pos), target_(pos){}
	Actor(ASCIISymbol symbol, Pos2D pos): symbol_(symbol), pos_(pos), target_(pos) {}
	ASCIISymbol symbol_ = ASCIISymbol();
	Pos2D GetPos() { return pos_; }
	void Draw(sf::RenderWindow& window, Spritesheet& font);
	void Update(World& world, float delta);
	bool AtTarget();
	void SetTarget(Pos2D pos) { target_ = pos; path_.reset(); }
	std::shared_ptr<Path> path_;
private:
	float movespeed_ = 15;
	float movetimer_ = 1 / movespeed_;
	void Move(World& world);
	bool ShouldMove(float delta);
	bool HasValidPath(World& world);
	Pos2D pos_ = Pos2D();
	Pos2D target_ = Pos2D();
	void ResetMoveTimer();
	void GetRandomTarget();
};