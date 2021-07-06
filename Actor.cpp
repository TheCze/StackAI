#pragma once
#include "ASCII.h"
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Path.h"
#include "Settings.h"
#include "Randomizer.h"

Actor::Actor()
{
	m_symbol = ASCIISymbol(ASCII::at, sf::Color::Red);
}
void Actor::draw(sf::RenderWindow& window, Spritesheet& font)
{
	m_symbol.draw(window, font, (float)m_pos.x, (float)m_pos.y);
}

void Actor::update(World& world, float delta)
{
	if (should_move(delta)) {
		if (has_valid_path(world)) {
			move(world);
			if (at_target())
				get_random_target();
		}
		else {
			m_path=world.get_path(m_pos, m_target);
			if (!m_path)
				get_random_target();
		}
	}
}

bool Actor::at_target() {
	return m_pos == m_target;
}

bool Actor::should_move(float delta) {
	m_movetimer -= delta;
	if (m_movetimer < 0) {

		reset_move_timer();
		return true;
	}
	return false;
}

bool Actor::has_valid_path(World& world)
{
	if (m_path && m_path->length()>0) {
		return true;
	}
	else {
		return false;
	}
}

void Actor::move(World& world)
{
	auto node = m_path->get_next();
	if (world.getPos(node->pos.x, node->pos.y).walkable) {
		m_pos = node->pos;
		world.getPos(m_pos).walk_on();
	}
	else {
		m_path.reset();		
	}
}

void Actor::reset_move_timer() {
	m_movetimer = 1 / m_movespeed;
}

void Actor::get_random_target()
{
	m_target.x = random::getInt(settings::WORLD_WIDTH-1);
	m_target.y = random::getInt(settings::WORLD_HEIGHT-1);	
	m_path.reset();
}
