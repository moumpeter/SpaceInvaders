#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "state.h"

int main()
{
    unsigned const screen_width{sf::VideoMode::getDesktopMode().width};
    unsigned const screen_height{sf::VideoMode::getDesktopMode().height};
    sf::RenderWindow window{sf::VideoMode{screen_width, screen_height}, "space invaders"};
    std::stack<State*> states{};
    states.push(new MenuState());

    sf::Clock clock;

    while(window.isOpen())
    {
        State* state{states.top()};
        sf::Event event;
        int pop_depth{0};
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            pop_depth = state->handle(event, states);
            if (pop_depth != 0) break;
            
        }
        state->update(clock.restart());
        window.clear();
        state->render(window);
        window.display();

        for (int i = 0; i < pop_depth; i++)
        {
            delete states.top();
            states.pop();
        }
    }
    while(!states.empty())
    {
        delete states.top();
        states.pop();

    }
    

}

