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
  GenerateMaze();
  pathfinder_.MapChangedAt(*this, Pos2D(0, 0));
}

void World::GenerateMaze() {
    DrawLine(Pos2D(10, 10), Pos2D(40, 10));
    DrawLine(Pos2D(10, 10), Pos2D(10, 20));
    DrawLine(Pos2D(20, 20), Pos2D(40, 40));
    DrawLine(Pos2D(25, 25), Pos2D(28, 29));
    DrawLine(Pos2D(20, 20), Pos2D(20, 40));
    DrawLine(Pos2D(1, 0), Pos2D(1, 10));
    DrawLine(Pos2D(30, 0), Pos2D(30, 8));
    DrawLine(Pos2D(35, 0), Pos2D(35, 9));
    DrawLine(Pos2D(30, 9), Pos2D(35, 8));
    DrawLine(Pos2D(32, 8), Pos2D(33, 7));
    DrawLine(Pos2D(10, 38), Pos2D(15, 38));
    DrawLine(Pos2D(5, 0), Pos2D(5, 9));
    DrawLine(Pos2D(15, 0), Pos2D(5, 9));
    DrawLine(Pos2D(42, 0), Pos2D(35, 19));
    DrawLine(Pos2D(23, 23), Pos2D(15, 19));
}

void World::GeneratePathfindingBenchmark() {
    DrawLine(Pos2D(10, 10), Pos2D(40, 10));
    DrawLine(Pos2D(10, 10), Pos2D(10, 20));
    DrawLine(Pos2D(20, 20), Pos2D(40, 40));
    DrawLine(Pos2D(25, 25), Pos2D(28, 29));
    DrawLine(Pos2D(20, 20), Pos2D(20, 40));
    DrawLine(Pos2D(1, 0), Pos2D(1, 10));
    DrawLine(Pos2D(30, 0), Pos2D(30, 8));
    DrawLine(Pos2D(35, 0), Pos2D(35, 9));
    DrawLine(Pos2D(30, 9), Pos2D(35, 8));
    DrawLine(Pos2D(32, 8), Pos2D(33, 7));
    DrawLine(Pos2D(10, 38), Pos2D(15, 38));
    DrawLine(Pos2D(5, 0), Pos2D(5, 9));
    DrawLine(Pos2D(15, 0), Pos2D(5, 9));
    DrawLine(Pos2D(42, 0), Pos2D(35, 19));
    DrawLine(Pos2D(23, 23), Pos2D(15, 19));
}

void World::DrawLine(Pos2D a, Pos2D b) {
    do{
        if(IsValid(a.x,a.y))
            SetWall(a,true);
        a.MoveTowards(b);
    } while (a != b);
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

std::shared_ptr<PathfinderCZ::Path> World::GetPath(Pos2D& start, Pos2D& target) {
    return pathfinder_.GetPath(*this, start, target);
}

void World::ToggleWalkable(Pos2D pos) {
    if (GetTile(pos).walkable_) {
        SetWall(pos, true);
    }
    else {
        SetWall(pos, false);
    }
    pathfinder_.MapChangedAt(*this, Pos2D(0, 0));
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
}

std::vector<Tile> World::GetAdjacents(Pos2D& pos) {
    std::vector<Tile> adjacents;
    adjacents.reserve(8);
    Pos2D up = pos.Adjacent(0, -1);
    Pos2D down = pos.Adjacent(0, 1);
    Pos2D left = pos.Adjacent(-1, 0);
    Pos2D right = pos.Adjacent(1, 0);
    TryAddingAdjacent(adjacents, up);
    TryAddingAdjacent(adjacents, down);
    TryAddingAdjacent(adjacents, left);
    TryAddingAdjacent(adjacents, right);


    Pos2D upleft = pos.Adjacent(-1, -1);
    Pos2D upright = pos.Adjacent(1, -1);
    Pos2D downleft = pos.Adjacent(-1, 1);
    Pos2D downright = pos.Adjacent(1, 1);
    if (CanBeEntered(up) && CanBeEntered(left))
            TryAddingAdjacent(adjacents, upleft);

    if (CanBeEntered(up) && CanBeEntered(right))
            TryAddingAdjacent(adjacents, upright);

    if (CanBeEntered(down) && CanBeEntered(right))
            TryAddingAdjacent(adjacents, downright);

    if (CanBeEntered(down) && CanBeEntered(left))
            TryAddingAdjacent(adjacents, downleft);
    return adjacents;
}

void World::TryAddingAdjacent(std::vector<Tile>& adjacents, Pos2D& pos) {
    if (CanBeEntered(pos))
        adjacents.push_back(GetTile(pos));
}

bool World::CanBeEntered(const Pos2D& pos) {
    return IsValid(pos) && GetTile(pos).walkable_;
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

