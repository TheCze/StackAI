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

bool mouse_right_pressed = false;

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
    actors.push_back(Actor(Pos2D(10,10)));
    actors.push_back(Actor(Pos2D(20, 10)));
    actors.push_back(Actor(Pos2D(30, 10)));
    actors.push_back(Actor(Pos2D(40, 10)));
    actors.push_back(Actor(Pos2D(50, 10)));
    actors.push_back(Actor(Pos2D(15, 20)));
    actors.push_back(Actor(Pos2D(25, 25)));
    actors.push_back(Actor(Pos2D(35, 10)));
    actors.push_back(Actor(Pos2D(45, 10)));
    actors.push_back(Actor(Pos2D(55, 10))); 
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
        actor.update(world, dt.asSeconds());
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
    for (auto& actor : actors) {
        /*if (actor.m_path) {
            ASCIISymbol p = ASCIISymbol(ASCII::hash, Color(50, 20, 150, 250));
            auto node = actor.m_path->first;
            node = node->next;
            while (node) {
                if (node->isLast())
                    p.setColor(Color::Red);
                p.draw(window, font, (float)node->pos.x, (float)node->pos.y);
                node = node->next;
            }
        }*/
        actor.Draw(window, font);
    }
    window.display();
}

void check_input(sf::RenderWindow& window, World& world)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int tile_x = mousePos.x / settings::TILE_WIDTH;
        int tile_y = mousePos.y / settings::TILE_WIDTH;
        if (world.IsValid(tile_x, tile_y)) {
            world.SetPos(tile_x, tile_y, ASCIISymbol(ASCII::block_full));
            world.GetTile(tile_x, tile_y).walkable_ = false;
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !mouse_right_pressed) {
        mouse_right_pressed = true;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int tile_x = mousePos.x / settings::TILE_WIDTH;
        int tile_y = mousePos.y / settings::TILE_WIDTH;
        if (world.IsValid(tile_x, tile_y)) {
            actors.front().set_target(Pos2D(tile_x, tile_y));
        }
    }
    else {
        mouse_right_pressed = false;
    }
}
