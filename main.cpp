#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Spritesheet.h"
#include "World.h"
#include "main.h"
#include "ASCII.h"
#include "Tile.h"
#include "Actor.h"


using namespace sf;

std::vector<Actor> actors;
sf::Clock deltaClock;


Texture* loadTexture(std::string path) {
    sf::Texture* texture = new Texture;
    if (texture->loadFromFile(path)) {        
        return texture;
    }
    else {
        std::cout << "ERROR LOADING TEXTURE " << path << std::endl;
        return nullptr;
    }
}


int main()
{
    Spritesheet font = Spritesheet(loadTexture("assets/terminal24.png"));
    actors.push_back(Actor(Pos2D(13, 7))); 
    sf::RenderWindow window(sf::VideoMode(settings::SCREEN_WIDTH, settings::SCREEN_HEIGTH), "Space");
    World world;
    world.pathfinder_.window_ = &window;
    world.pathfinder_.font_ = &font;

    while (window.isOpen())
    {
        check_input(window, world);
        update(world);
        render(window, world, font);
    }
    return 0;
}

void update(World& world) {
    sf::Time dt = deltaClock.restart();
    if (dt.asMilliseconds() > 100) {
       std::cout << "Hickup: " << dt.asMilliseconds() << " ms " <<std::endl;
        //while (deltaClock.getElapsedTime().asSeconds() < 5){
        //}
        //    deltaClock.restart();
    }
    world.Update(dt.asSeconds());
    for (auto& actor : actors) {
        actor.Update(world, dt.asSeconds());
    }
}

void render(sf::RenderWindow& window, World& world, Spritesheet& font)
{
    window.clear();
    for (int x = 0; x < settings::WORLD_WIDTH; x++) {
        for (int y = 0; y < settings::WORLD_HEIGHT; y++) {
           world.GetTile(x, y).symbol_.Draw(window,font,x,y);
        }
    }

    for (auto navrec : world.pathfinder_.navrecs) {
        sf::Color c = sf::Color::Blue;
        if (navrec->current_heuristic == -1) {
            c = sf::Color::Red;
            auto neighbors = navrec->neighbors;
        }
        else
            c.a = navrec->current_heuristic;
       ASCIISymbol box = ASCIISymbol(ASCII::filled, c);
        box.Draw(window, font, navrec->start, navrec->size);
    }

    for (auto& actor : actors) {
        if (actor.path_) {
            ASCIISymbol p = ASCIISymbol(ASCII::hash, Color(50, 20, 150, 250));
            auto node = actor.path_->first;
            node = node->next;
            while (node) {
                if (node->IsLast())
                    p.SetColor(Color::Red);
                p.Draw(window, font, (float)node->pos.x, (float)node->pos.y);
                node = node->next;
            }
        }
        actor.Draw(window, font);
    }
    window.display();
}
bool mouse_l_pressed = false;
bool mouse_r_pressed = false;
void check_input(sf::RenderWindow& window, World& world)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    sf::Vector2i sfmousePos = sf::Mouse::getPosition(window);
    int tile_x = sfmousePos.x / settings::TILE_WIDTH;
    int tile_y = sfmousePos.y / settings::TILE_WIDTH;
    Pos2D mousepos = Pos2D(tile_x, tile_y);
    if (!world.IsValid(mousepos)) {
        return;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        world.SetWall(mousepos, true);
        world.pathfinder_.UpdateNavRec(world, Pos2D(0, 0));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        world.SetWall(mousepos, false);
        world.pathfinder_.UpdateNavRec(world, Pos2D(0, 0));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int tile_x = mousePos.x / settings::TILE_WIDTH;
        int tile_y = mousePos.y / settings::TILE_WIDTH;
        if (world.IsValid(tile_x, tile_y)) {
            actors.front().SetTarget(Pos2D(tile_x, tile_y));
        }
    }
}
