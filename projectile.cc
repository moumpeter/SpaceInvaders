#include "game_object.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Projectile::Projectile(sf::Vector2f init_pos, std::string init_dir)
    : GameObject{init_pos}, proj_speed{1000.f}, proj_size{5,15}, dir{init_dir}
    {
        shape.setFillColor(sf::Color::White);
        shape.setSize({5,15});
        shape.setOrigin(proj_size.x/2, proj_size.y);
    }
void Projectile::handle(sf::Event event)
{

}
void Projectile::update(sf::Time delta, std::vector<GameObject*>& new_objects)
{
    
    float distance{delta.asSeconds()* proj_speed};
    sf::Vector2f move{0.f,0.f};
    if (dir == "up")
    {
        move.y -= distance;
    }
    else if (dir == "down")
    {
        move.y += distance;
    }
    
    pos += move*distance;
    shape.setPosition(pos);
}

void Projectile::render(sf::RenderWindow& window)
{
    window.draw(shape);
}