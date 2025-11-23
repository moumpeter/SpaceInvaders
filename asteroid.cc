#include "game_object.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Asteroid::Asteroid(sf::Vector2f init_pos, sf::Texture init_texture)
    :GameObject{init_pos}
    {
        texture{init_texture};
        if (!texture.loadFromFile("assets")) {
            std::cerr << "Failed to load texture\n";
        }
        sprite.setTexture(texture);
        sprite.setPosition(pos);
        sf::FloatRect bounds = sprite.getLocalBounds();
    }

void Asteroid::handle(sf::Event event)
{
    
}

void Asteroid::update(sf::Time delta, std::vector<GameObject*>& new_objects)
{
}

void Asteroid::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}
