#include "state.h"

GameState::GameState()
    : gameobjects{}, projectiles{}
{   
    sf::Vector2u screen_size{sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height-100};
    sf::Vector2f screen_sizef{screen_size};
    player = new Player(screen_sizef);
    int enemy_row{14};

    for(int i{1}; i <= enemy_row; i++)
    {
        gameobjects.push_back(new Enemy({(screen_size.x-20)*i/8, screen_size.y/3-100}));
    }
    for(int i{1}; i <= enemy_row; i++)
    {
        gameobjects.push_back(new Enemy({(screen_size.x-20)*i/8, screen_size.y/3-200}));
    }
    for(int i{1}; i <= enemy_row; i++)
    {
        gameobjects.push_back(new Enemy({(screen_size.x-20)*i/8, screen_size.y/3-300}));
    }
    for(int i{1}; i <= enemy_row; i++)
    {
        gameobjects.push_back(new Enemy({(screen_size.x-20)*i/8, screen_size.y/3-400}));
    }
    for(int i{1}; i <= enemy_row; i++)
    {
        gameobjects.push_back(new Enemy({(screen_size.x-20)*i/8, screen_size.y/3-500}));
    }
   
   
   
    //gameobjects.push_back(p1);
    //gameobjects.push_back(new Player{{500,600}});
}

GameState::~GameState()
{
    
    /*while (!gameobjects.empty())
    {
        delete gameobjects.back();
        gameobjects.pop_back();
    }*/
   delete player;
    while (!projectiles.empty())
    {
        delete projectiles.back();
        projectiles.pop_back();
    }
    while (!gameobjects.empty())
    {
        delete gameobjects.back();
        gameobjects.pop_back();
    }

}
int GameState::handle(sf::Event event, std::stack<State*>& states)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Escape)
        {
            return 1;
        }
        if (event.key.code == sf::Keyboard::Key:: Space)
        {
            projectiles.push_back(new Projectile{player -> get_pos(),  "up"});
        }
    }
    player -> handle(event);
    for (auto projectile : projectiles)
    {
        projectile->handle(event);
    }
    
    for(auto enemy : gameobjects)
    {
        enemy -> handle(event);
    }
    
    return 0;
}

void GameState::update(sf::Time delta)
{
    std::vector<GameObject*> new_objects{};
    player -> update(delta, new_objects);
    for (auto object : projectiles)
    {
        object->update(delta, new_objects);

    }
    //for (auto object: new_objects)
    //{
    //    object -> update(delta, new_objects);
    //}
    for (auto enemy: gameobjects)
    {
        
        enemy -> update(delta, new_objects);
        
    }

    // TODO: Kolla kollisioner
    // for ()
    // {
    // }

    // Döda objekt, loopar baklänges för att undvika index-problem
    for (unsigned int i = projectiles.size(); i-- > 0;)
    {
        if (projectiles[i]->is_dead() ||(projectiles[i] -> get_pos().y <0))
        {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
    }

    // Lägg till nya objekt sist
    /*for (auto new_object : new_objects)
    {
        // Lägg till det nya objektet
        projectiles.push_back(new_object);
    }*/
}

void GameState::render(sf::RenderWindow& window)
{
    player -> render(window);
    for (auto projectile : projectiles)
    {
        projectile->render(window);
    }
     
    for(auto enemy: gameobjects)
    {
        enemy -> render(window);
    }
    
    
}



MenuState::MenuState()
    : textobjects{}, font{}
// : font{}, text{}, elapsed_time{0.0f}
{
    // TODO: Lägg in text som behövs

    // För att skriva ut en text i SFML så måste vi ladda in ett
    // typsnitt. Detta hanteras på liknande sätt som texturer.
    // OBS: Font måste existera sålänge vårt text objekt ska
    // existera.

    if (!font.loadFromFile("font.ttf"))
    {
        throw std::runtime_error{"Kan inte öppna: font.ttf"};
    }

    // Initiera text objektet som representerar vår text som ska
    // skrivas ut.

    sf::Text text{};
    text.setFont(font);
    text.setString("Press <Enter> to start!");

    // För att placera texten i mitten av skärmen måste vi veta
    // bredden och höjden av texten. För att få ut detta kan vi
    // använda vår käre vän .getGlobalbounds()!

    sf::FloatRect bounds{text.getGlobalBounds()};

    text.setOrigin(bounds.width / 2, bounds.height / 2);
    text.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);

    // Pusha texten för att rendera den
    textobjects.push_back(text);
}

int MenuState::handle(sf::Event event, std::stack<State*>& states)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Enter)
        {
            states.push(new GameState());
        }
    }
    return 0;
    
}

void MenuState::update(sf::Time delta)
{
  
}

void MenuState::render(sf::RenderWindow& window)
{
    for (auto text : textobjects)
    {
        window.draw(text);
    }
    // window.draw(text);
}