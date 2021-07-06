#pragma once
#include <SFML/Graphics.hpp>
#include "ASCIISymbol.h"
#include "World.h"
#include "Pos2D.h"
#include "Path.h"
class Actor {
public: 
	Actor();
	Actor(Pos2D pos) : symbol_(ASCIISymbol(ASCII::face,sf::Color::Red)), pos_(pos), m_target(pos){}
	Actor(ASCIISymbol symbol, Pos2D pos): symbol_(symbol), pos_(pos), m_target(pos) {}
	ASCIISymbol symbol_ = ASCIISymbol();
	Pos2D pos() { return pos_; }
	void Draw(sf::RenderWindow& window, Spritesheet& font);
	void update(World& world, float delta);
	bool at_target();
	void set_target(Pos2D pos) { m_target = pos; m_path.reset(); }
	std::shared_ptr<Path> m_path;
private:
	float m_movespeed = 15;
	float m_movetimer = 1 / m_movespeed;
	void move(World& world);
	bool should_move(float delta);
	bool has_valid_path(World& world);
	Pos2D pos_ = Pos2D();
	Pos2D m_target = Pos2D();
	void reset_move_timer();
	void get_random_target();
};