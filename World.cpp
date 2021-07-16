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
      GetTile(x, y).symbol_.SetBGColor(sf::Color(0, 100, 0, 255));
      GetTile(x, y).defaultColor_=sf::Color(0, 100, 0, 255);
      GetTile(x, y).usageColor_ = sf::Color(90, 60, 25, 130);
      tiles_[XY(x, y)].symbol_.RandomizeShade(20);
    }
  }
  //PlaceRandomStones();
  pathfinder_.UpdateNavRec(*this, Pos2D(0, 0));
}

void World::PlaceRandomStones() {
    for (int i = 0; i < 100; i++) {
        int x = random::getInt(settings::WORLD_WIDTH-1);
        int y = random::getInt(settings::WORLD_HEIGHT-1);
        SetPos(x, y, ASCIISymbol(ASCII::sun, sf::Color(50, 50, 50, 235)));
        GetTile(x, y).SetDefaultTileCost(5);
        GetTile(x, y).symbol_.SetBGColor(sf::Color(0, 100, 0, 255));
        GetTile(x, y).defaultColor_ = sf::Color(0, 100, 0, 255);
        GetTile(x, y).usageColor_ = sf::Color(50, 50, 50, 100);
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
                GetTile(x, y).Renaturalize();
            }
        }
    }
}

void World::ClearPathDebugWorld() {
    for (int x = 0; x < kTilesWidth; x++) {
        for (int y = 0; y < kTilesHeight; y++) {
            if(GetTile(x,y).walkable_)
                GetTile(x, y).symbol_.SetColor(sf::Color(20, 50, 20, 0));
        }
    }
}

std::shared_ptr<Path> World::GetPath(Pos2D& start, Pos2D& target) {
    return pathfinder_.GetPath(*this, start, target);
}

void World::ToggleWalkable(Pos2D pos) {
    if (GetTile(pos).walkable_) {
        GetTile(pos).symbol_.SetTileCode(ASCII::block_full);
        GetTile(pos).symbol_.SetColor(sf::Color::White);
        GetTile(pos).walkable_ = false;
    }
    else {
        GetTile(pos).symbol_.SetTileCode(ASCII::get_random_ground());
        GetTile(pos).symbol_.SetColor(sf::Color(20, 100, 20, 235));
        GetTile(pos).symbol_.SetBGColor(sf::Color(0, 100, 0, 255));
        GetTile(pos).defaultColor_ = sf::Color(0, 100, 0, 255);
        GetTile(pos).usageColor_ = sf::Color(90, 60, 25, 130);
        GetTile(pos).walkable_ = true;
    }
}

void World::SetWall(Pos2D pos, bool place) {
    if (place) {
        GetTile(pos).symbol_.SetTileCode(ASCII::block_full);
        GetTile(pos).symbol_.SetColor(sf::Color::White);
        GetTile(pos).walkable_ = false;
    }
    else {
        GetTile(pos).symbol_.SetTileCode(ASCII::get_random_ground());
        GetTile(pos).symbol_.SetColor(sf::Color(20, 100, 20, 235));
        GetTile(pos).symbol_.SetBGColor(sf::Color(0, 100, 0, 255));
        GetTile(pos).defaultColor_ = sf::Color(0, 100, 0, 255);
        GetTile(pos).usageColor_ = sf::Color(90, 60, 25, 130);
        GetTile(pos).walkable_ = true;
    }
    pathfinder_.UpdateNavRec(*this, Pos2D(0, 0));
}

std::vector<Tile> World::GetAdjacents(Pos2D& pos) {
    std::vector<Tile> adjacents;
    Pos2D up = pos.Adjacent(0, -1);
    Pos2D down = pos.Adjacent(0, 1);
    Pos2D left = pos.Adjacent(-1, 0);
    Pos2D right = pos.Adjacent(1, 0);
    if (IsValid(up) && GetTile(up).walkable_)
        adjacents.push_back(GetTile(up));
    if (IsValid(down) && GetTile(down).walkable_)
        adjacents.push_back(GetTile(down));
    if (IsValid(left) && GetTile(left).walkable_)
        adjacents.push_back(GetTile(left));
    if (IsValid(right) && GetTile(right).walkable_)
        adjacents.push_back(GetTile(right));

    Pos2D upleft = pos.Adjacent(-1, -1);
    Pos2D upright = pos.Adjacent(1, -1);
    Pos2D downleft = pos.Adjacent(-1, 1);
    Pos2D downright = pos.Adjacent(1, 1);
    if (IsValid(up) && GetTile(up).walkable_)
        if (IsValid(left) && GetTile(left).walkable_)
            if (IsValid(upleft) && GetTile(upleft).walkable_)
                adjacents.push_back(GetTile(upleft));

    if (IsValid(up) && GetTile(up).walkable_)
        if (IsValid(right) && GetTile(right).walkable_)
            if (IsValid(upright) && GetTile(upright).walkable_)
                adjacents.push_back(GetTile(upright));

    if (IsValid(down) && GetTile(down).walkable_)
        if (IsValid(right) && GetTile(right).walkable_)
            if (IsValid(downright) && GetTile(downright).walkable_)
                adjacents.push_back(GetTile(downright));

    if (IsValid(down) && GetTile(down).walkable_)
        if (IsValid(left) && GetTile(left).walkable_)
            if (IsValid(downleft) && GetTile(downleft).walkable_)
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

