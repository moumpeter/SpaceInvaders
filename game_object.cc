#include "game_object.h"

GameObject::GameObject(sf::Vector2f init_pos)
    :pos{init_pos}, dead{false}, sprite{}
{}

bool GameObject::is_dead() const
{
    return dead;
}

sf::Vector2f GameObject::get_pos()
{
    return pos;
}