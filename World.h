#pragma once
#include "Settings.h"
#include "Tile.h"
#include "Pathfinder.h"
#include "Pos2D.h"
#include "Path.h"
class World {
 public:
  World();
  ~World();
  static const int kTilesWidth = settings::WORLD_WIDTH;
  static const int kTilesHeight = settings::WORLD_HEIGHT;
  Tile* tiles_;
  Tile& GetTile(int x, int y) { return tiles_[XY(x, y)];}
  Tile& GetTile(Pos2D pos) { return GetTile(pos.x, pos.y); }
  void SetPos(int x, int y, Tile t) { t.m_pos.x = x; t.m_pos.y = y; tiles_[XY(x, y)] = t; }
  std::shared_ptr<Path> GetPath(Pos2D start, Pos2D target);
  std::vector<Tile> GetAdjacents(Pos2D);
  bool IsValid(int x, int y) { return x < kTilesWidth&& y < kTilesHeight && x >= 0 && y >= 0; }
  bool IsValid(Pos2D pos) { return IsValid(pos.x,pos.y); }
  Pathfinder pathfinder_;
  void ClearPathDebugWorld();
  void Update(float delta);
 private:
  void InitWorld();
  void PlaceRandomStones();
  void Renaturalize(float delta);
  int XY(int& x, int& y);
  float kRenaturalizationPercentage = 0.001f;
  float renaturalization_time_ = 1.0f;
};
