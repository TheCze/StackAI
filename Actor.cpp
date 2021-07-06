#pragma once
#include "ASCII.h"
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Path.h"
#include "Settings.h"
#include "Randomizer.h"

Actor::Actor()
{
	symbol_ = ASCIISymbol(ASCII::at, sf::Color::Red);
}
void Actor::Draw(sf::RenderWindow& window, Spritesheet& font)
{
	symbol_.Draw(window, font, (float)pos_.x, (float)pos_.y);
}

void Actor::Update(World& world, float delta)
{
	if (ShouldMove(delta)) {
		if (HasValidPath(world)) {
			Move(world);
			if (AtTarget())
				GetRandomTarget();
		}
		else {
			path_=world.GetPath(pos_, target_);
			if (!path_)
				GetRandomTarget();
		}
	}
}

bool Actor::AtTarget() {
	return pos_ == target_;
}

bool Actor::ShouldMove(float delta) {
	movetimer_ -= delta;
	if (movetimer_ < 0) {

		ResetMoveTimer();
		return true;
	}
	return false;
}

bool Actor::HasValidPath(World& world)
{
	if (path_ && path_->length()>0) {
		return true;
	}
	else {
		return false;
	}
}

void Actor::Move(World& world)
{
	auto node = path_->get_next();
	if (world.GetTile(node->pos.x, node->pos.y).walkable_) {
		pos_ = node->pos;
		world.GetTile(pos_).WalkOn();
	}
	else {
		path_.reset();		
	}
}

void Actor::ResetMoveTimer() {
	movetimer_ = 1 / movespeed_;
}

void Actor::GetRandomTarget()
{
	target_.x = random::getInt(settings::WORLD_WIDTH-1);
	target_.y = random::getInt(settings::WORLD_HEIGHT-1);	
	path_.reset();
}
