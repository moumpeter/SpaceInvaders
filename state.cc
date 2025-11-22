#include "state.h"

GameState::GameState()
    : gameobjects{}
{   
    sf::Vector2u screen_size{sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height-100};
    sf::Vector2f screen_sizef{screen_size};
    player = new Player(screen_sizef);
    //gameobjects.push_back(p1);
    //gameobjects.push_back(new Player{{500,600}});
}

GameState::~GameState()
{
    
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
            gameobjects.push_back(new Projectile{player -> get_pos(),  "up"});
        }
    }
    player -> handle(event);
    for (auto gameobject : gameobjects)
    {
        gameobject->handle(event);
    }
    for (auto object: new_objects)
    {
        object -> handle(event);
    }
    return 0;
}

void GameState::update(sf::Time delta)
{
    // TODO: Flytta fiender mot spelaren och flytta spelaren
    std::vector<GameObject*> new_objects{};
    player -> update(delta, new_objects);
    for (auto object : gameobjects)
    {
        object->update(delta, new_objects);

    }
    for (auto object: new_objects)
    {
        object -> update(delta, new_objects);
    }


    // TODO: Kolla kollisioner
    // for ()
    // {
    // }

    // Döda objekt, loopar baklänges för att undvika index-problem
    for (unsigned int i = gameobjects.size(); i-- > 0;)
    {
        if (gameobjects[i]->is_dead() ||(gameobjects[i] -> get_pos().y <0))
        {
            delete gameobjects[i];
            gameobjects.erase(gameobjects.begin() + i);
        }
    }

    // Lägg till nya objekt sist
    for (auto new_object : new_objects)
    {
        // Lägg till det nya objektet
        gameobjects.push_back(new_object);
    }
}

void GameState::render(sf::RenderWindow& window)
{
    player -> render(window);
    for (auto object : gameobjects)
    {
        object->render(window);
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
    // Tycker vår meny ska vara statisk, dvs denna behövs inte just nu

    //                                       // Öka tiden som har gått.
    //                                       elapsed_time += delta.asSeconds();

    // // En full cykel av pulsering för texten ska ta 2 sekunder.
    // float const period{2.0f};

    // // Omskalningsfaktorn är i intervallet [0.9, 1.1], vi använder
    // // sin för att få det periodiska beteendet.  OBS: std::sin
    // // använder radianer medan SFML använder grader för vinklar.
    // double const scale{1.0 + 0.1 * std::sin((2 * M_PI) * elapsed_time / period)};
    // text.setScale(scale, scale);
}

void MenuState::render(sf::RenderWindow& window)
{
    for (auto text : textobjects)
    {
        window.draw(text);
    }
    // window.draw(text);
}