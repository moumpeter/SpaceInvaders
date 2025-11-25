#include "game_object.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Projectile::Projectile(sf::Vector2f init_pos, std::string init_dir)
    : GameObject{init_pos}, proj_speed{175.f}, proj_size{0.025f, 0.075f}, dir{init_dir}
    {
        if(!texture.loadFromFile("assets/Turquoise.png")) 
        {
            std::cerr << "Failed to load texture\n";
        }
        sprite.setScale(proj_size);
        sprite.setTexture(texture);
        sprite.setPosition(pos);
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
    sprite.setPosition(pos);
}

void Projectile::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}