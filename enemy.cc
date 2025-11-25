#include "game_object.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Enemy::Enemy(sf::Vector2f init_pos)
    :GameObject{init_pos}, speed{300}, timer{0.f}, dir{-1}
    {
        if (!texture.loadFromFile("assets/yellow.png")) {
            std::cerr << "Failed to load texture\n";
        }
        sprite.setTexture(texture);
        sprite.setPosition(pos);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width/2, 0);
    }

void Enemy::handle(sf::Event event)
{
    
}
void Enemy::update(sf::Time delta, std::vector<GameObject*>& new_objects)
{
    float distance{delta.asSeconds()* speed};
    float old_pos = pos.y;
    
    timer += delta.asSeconds();
    if(timer >= 0.5f)    
    {
        pos.x += dir*distance*5;
        if(pos.x < 15)
        {
            pos.x = 15;
            pos.y = old_pos + 50;
            dir = 1;
            
        }
        if(pos.x >= sf::VideoMode::getDesktopMode().width -75)
        {
            pos.x =  sf::VideoMode::getDesktopMode().width -75;
            pos.y = old_pos + 50;
            dir = -1;

        }
        
        timer = 0.f;
    }
    sprite.setPosition(pos);
}

void Enemy::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}