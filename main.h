#pragma once

void check_input(sf::RenderWindow& window, World& world);
void update(World& world);
void RunGame(sf::RenderWindow& window, World& world, Spritesheet& font);
void RunPathfindingBenchmark(World& world);
void render(sf::RenderWindow& window, World& world, Spritesheet& font);
