#include <SFML/Graphics.hpp>
#include <cmath>
#include <stack>
#include <stdexcept>
#include "game_object.h"

class State
{
    public:
    virtual ~State() = default;
    virtual int handle(sf::Event event, std::stack<State*>& states) = 0;
    virtual void update(sf::Time delta) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

class GameState : public State
{
    public:
    GameState();
    ~GameState();
    int handle(sf::Event event, std::stack<State*>& states) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;
    private:
    std::vector<GameObject*> gameobjects;
    std::vector<GameObject*> new_objects;
    std::vector<GameObject*> projectiles;
    GameObject* player;
};

class MenuState : public State
{
   public:
    MenuState();
    int handle(sf::Event event, std::stack<State*>& states) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

   private:
    std::vector<sf::Text> textobjects;
    sf::Font font;
    //     sf::Text text;
    //     float elapsed_time;
};