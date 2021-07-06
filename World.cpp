#pragma once
#include "World.h"
#include "ASCII.h"
World::World() {
  initWorld(); }

World::~World() { delete tiles; }

void World::initWorld() {
  tiles = new Tile[tiles_h * tiles_w];
  for (int x = 0; x < tiles_w; x++) {
    for (int y = 0; y < tiles_h; y++) {
      setPos(x, y, ASCIISymbol(ASCII::get_random_ground(), sf::Color(20, 100, 20, 235)));
      getPos(x, y).m_symbol.setBGColor(sf::Color(0, 100, 0, 255));
      getPos(x, y).defaultColor=sf::Color(0, 100, 0, 255);
      getPos(x, y).usageColor = sf::Color(90, 60, 25, 130);
      tiles[xy(x, y)].m_symbol.randomize_shade(20);
    }
  }
  placeRandomStones();
}

void World::placeRandomStones() {
    for (int i = 0; i < 100; i++) {
        int x = random::getInt(settings::WORLD_WIDTH-1);
        int y = random::getInt(settings::WORLD_HEIGHT-1);
        setPos(x, y, ASCIISymbol(ASCII::sun, sf::Color(50, 50, 50, 235)));
        getPos(x, y).SetDefaultTileCost(5);
        getPos(x, y).m_symbol.setBGColor(sf::Color(0, 100, 0, 255));
        getPos(x, y).defaultColor = sf::Color(0, 100, 0, 255);
        getPos(x, y).usageColor = sf::Color(50, 50, 50, 100);
    }
}

void World::update(float delta) {
    renaturalize(delta);
}

void World::renaturalize(float delta) {
    renaturalization_time -= delta;
    if (renaturalization_time < 0) {
        int amount = settings::WORLD_HEIGHT * settings::WORLD_HEIGHT * renaturalization_perc;
        for (int i = 0; i < amount; i++) {
            int x = random::getInt(settings::WORLD_WIDTH - 1);
            int y = random::getInt(settings::WORLD_HEIGHT - 1);
            if (is_valid(x, y)) {
                getPos(x, y).renaturalize();
            }
        }
    }
}

void World::clearWorld() {
    for (int x = 0; x < tiles_w; x++) {
        for (int y = 0; y < tiles_h; y++) {
            if(getPos(x,y).walkable)
                getPos(x, y).m_symbol.setColor(sf::Color(20, 50, 20, 0));
        }
    }
}

std::shared_ptr<Path> World::get_path(Pos2D start, Pos2D target) {
    return pathfinder.getPath(*this, start, target);
}

std::vector<Tile> World::get_adjacents(Pos2D pos) {
    std::vector<Tile> adjacents;
    Pos2D up = pos.adjacent(0, -1);
    Pos2D down = pos.adjacent(0, 1);
    Pos2D left = pos.adjacent(-1, 0);
    Pos2D right = pos.adjacent(1, 0);
    if (is_valid(up) && getPos(up).walkable)
        adjacents.push_back(getPos(up));
    if (is_valid(down) && getPos(down).walkable)
        adjacents.push_back(getPos(down));
    if (is_valid(left) && getPos(left).walkable)
        adjacents.push_back(getPos(left));
    if (is_valid(right) && getPos(right).walkable)
        adjacents.push_back(getPos(right));

    Pos2D upleft = pos.adjacent(-1, -1);
    Pos2D upright = pos.adjacent(1, -1);
    Pos2D downleft = pos.adjacent(-1, 1);
    Pos2D downright = pos.adjacent(1, 1);
    if (is_valid(up) && getPos(up).walkable)
        if (is_valid(left) && getPos(left).walkable)
            if (is_valid(upleft) && getPos(upleft).walkable)
                adjacents.push_back(getPos(upleft));

    if (is_valid(up) && getPos(up).walkable)
        if (is_valid(right) && getPos(right).walkable)
            if (is_valid(upright) && getPos(upright).walkable)
                adjacents.push_back(getPos(upright));

    if (is_valid(down) && getPos(down).walkable)
        if (is_valid(right) && getPos(right).walkable)
            if (is_valid(downright) && getPos(downright).walkable)
                adjacents.push_back(getPos(downright));

    if (is_valid(down) && getPos(down).walkable)
        if (is_valid(left) && getPos(left).walkable)
            if (is_valid(downleft) && getPos(downleft).walkable)
                adjacents.push_back(getPos(downleft)); 
 

    return adjacents;
}

int World::xy(int& x, int& y) {
    if (is_valid(x, y)) {
        return x + y * tiles_w;
    }
    else { 
        std::cout << "ILLEGAL ACCESS: " <<x<<"/"<<y<<std::endl;
        return 0;
    }
}

