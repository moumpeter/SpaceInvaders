#include "game_object.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player(sf::Vector2f init_pos)
    : GameObject{init_pos}, speed{1000.f}
    {
        if (!texture.loadFromFile("assets/player.png")) {
            std::cerr << "Failed to load texture\n";
        }
        sprite.setTexture(texture);
        sprite.setPosition(pos);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width/2, 0);
    }
void Player::handle(sf::Event event)
{

}
void Player::update(sf::Time delta, std::vector<GameObject*>& new_objects)
{
    
    float distance{delta.asSeconds()* speed};
    sf::Vector2f move{0.f,0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
       move.x += distance;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
       move.x -= distance;
    }
    pos += move*distance;
    sprite.setPosition(pos);
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}