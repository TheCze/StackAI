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
  static const int tiles_w = settings::WORLD_WIDTH;
  static const int tiles_h = settings::WORLD_HEIGHT;
  Tile* tiles;
  Tile& getPos(int x, int y) { return tiles[xy(x, y)];}
  Tile& getPos(Pos2D pos) { return getPos(pos.x, pos.y); }
  void setPos(int x, int y, Tile t) { t.m_pos.x = x; t.m_pos.y = y; tiles[xy(x, y)] = t; }
  std::shared_ptr<Path> get_path(Pos2D start, Pos2D target);
  std::vector<Tile> get_adjacents(Pos2D);
  bool is_valid(int x, int y) { return x < tiles_w&& y < tiles_h && x >= 0 && y >= 0; }
  bool is_valid(Pos2D pos) { return is_valid(pos.x,pos.y); }
  Pathfinder pathfinder;
  void clearWorld();
  void update(float delta);
 private:
  void initWorld();
  void placeRandomStones();
  void renaturalize(float delta);
  int xy(int& x, int& y);
  float renaturalization_perc = 0.001f;
  float renaturalization_time = 1.0f;
};
