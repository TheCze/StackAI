#pragma once
#include "World.h"
#include "ASCII.h"
World::World() {
  InitWorld(); }

World::~World() { delete tiles_; }

void World::InitWorld() {
  tiles_ = new Tile[kTilesHeight * kTilesWidth];
  for (int x = 0; x < kTilesWidth; x++) {
    for (int y = 0; y < kTilesHeight; y++) {
      SetPos(x, y, ASCIISymbol(ASCII::get_random_ground(), sf::Color(20, 100, 20, 235)));
      GetTile(x, y).m_symbol.setBGColor(sf::Color(0, 100, 0, 255));
      GetTile(x, y).defaultColor=sf::Color(0, 100, 0, 255);
      GetTile(x, y).usageColor = sf::Color(90, 60, 25, 130);
      tiles_[XY(x, y)].m_symbol.randomize_shade(20);
    }
  }
  PlaceRandomStones();
}

void World::PlaceRandomStones() {
    for (int i = 0; i < 100; i++) {
        int x = random::getInt(settings::WORLD_WIDTH-1);
        int y = random::getInt(settings::WORLD_HEIGHT-1);
        SetPos(x, y, ASCIISymbol(ASCII::sun, sf::Color(50, 50, 50, 235)));
        GetTile(x, y).SetDefaultTileCost(5);
        GetTile(x, y).m_symbol.setBGColor(sf::Color(0, 100, 0, 255));
        GetTile(x, y).defaultColor = sf::Color(0, 100, 0, 255);
        GetTile(x, y).usageColor = sf::Color(50, 50, 50, 100);
    }
}

void World::Update(float delta) {
    Renaturalize(delta);
}

void World::Renaturalize(float delta) {
    renaturalization_time_ -= delta;
    if (renaturalization_time_ < 0) {
        int amount = settings::WORLD_HEIGHT * settings::WORLD_HEIGHT * kRenaturalizationPercentage;
        for (int i = 0; i < amount; i++) {
            int x = random::getInt(settings::WORLD_WIDTH - 1);
            int y = random::getInt(settings::WORLD_HEIGHT - 1);
            if (IsValid(x, y)) {
                GetTile(x, y).renaturalize();
            }
        }
    }
}

void World::ClearPathDebugWorld() {
    for (int x = 0; x < kTilesWidth; x++) {
        for (int y = 0; y < kTilesHeight; y++) {
            if(GetTile(x,y).walkable)
                GetTile(x, y).m_symbol.setColor(sf::Color(20, 50, 20, 0));
        }
    }
}

std::shared_ptr<Path> World::GetPath(Pos2D start, Pos2D target) {
    return pathfinder_.GetPath(*this, start, target);
}

std::vector<Tile> World::GetAdjacents(Pos2D pos) {
    std::vector<Tile> adjacents;
    Pos2D up = pos.adjacent(0, -1);
    Pos2D down = pos.adjacent(0, 1);
    Pos2D left = pos.adjacent(-1, 0);
    Pos2D right = pos.adjacent(1, 0);
    if (IsValid(up) && GetTile(up).walkable)
        adjacents.push_back(GetTile(up));
    if (IsValid(down) && GetTile(down).walkable)
        adjacents.push_back(GetTile(down));
    if (IsValid(left) && GetTile(left).walkable)
        adjacents.push_back(GetTile(left));
    if (IsValid(right) && GetTile(right).walkable)
        adjacents.push_back(GetTile(right));

    Pos2D upleft = pos.adjacent(-1, -1);
    Pos2D upright = pos.adjacent(1, -1);
    Pos2D downleft = pos.adjacent(-1, 1);
    Pos2D downright = pos.adjacent(1, 1);
    if (IsValid(up) && GetTile(up).walkable)
        if (IsValid(left) && GetTile(left).walkable)
            if (IsValid(upleft) && GetTile(upleft).walkable)
                adjacents.push_back(GetTile(upleft));

    if (IsValid(up) && GetTile(up).walkable)
        if (IsValid(right) && GetTile(right).walkable)
            if (IsValid(upright) && GetTile(upright).walkable)
                adjacents.push_back(GetTile(upright));

    if (IsValid(down) && GetTile(down).walkable)
        if (IsValid(right) && GetTile(right).walkable)
            if (IsValid(downright) && GetTile(downright).walkable)
                adjacents.push_back(GetTile(downright));

    if (IsValid(down) && GetTile(down).walkable)
        if (IsValid(left) && GetTile(left).walkable)
            if (IsValid(downleft) && GetTile(downleft).walkable)
                adjacents.push_back(GetTile(downleft));
 

    return adjacents;
}

int World::XY(int& x, int& y) {
    if (IsValid(x, y)) {
        return x + y * kTilesWidth;
    }
    else { 
        std::cout << "ILLEGAL ACCESS: " <<x<<"/"<<y<<std::endl;
        return 0;
    }
}

