#include "game_object.h"

GameObject::GameObject(sf::Vector2f init_pos)
    :pos{init_pos}, sprite{},dead{false}
{}

bool GameObject::is_dead() const
{
    return dead;
}

sf::Vector2f GameObject::get_pos()
{
    return pos;
}
sf::FloatRect GameObject::get_bounds() 
{
    return sprite.getGlobalBounds();
}
void GameObject::update_dead(bool var)
{
    dead = var;
}

void GameObject::collides(GameObject* game_object)
{
    if(get_bounds().intersects(game_object->get_bounds()))
    {
        dead = true;
        game_object -> update_dead(true);
    }
}