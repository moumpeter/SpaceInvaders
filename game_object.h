#include <SFML/Graphics.hpp>
#include <string>

class GameObject
{
    public:

    virtual void handle(sf::Event event) = 0;
    virtual void update(sf::Time delta, std::vector<GameObject*>& new_objects) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~GameObject() = default;
    GameObject(sf::Vector2f init_pos);
    bool is_dead() const;
    //virtual bool colllides() = 0;
    sf::Vector2f get_pos();

    protected:
    sf::Vector2f pos;
    sf::Sprite sprite;
    float speed;
    bool dead;

};

class Enemy : public GameObject
{
    public:
    void handle(sf::Event event) override;
    void update(sf::Time delta, std::vector<GameObject*>& new_objects) override;
    void render(sf::RenderWindow& window) override;
    //bool collides() override;
};
class Player: public GameObject
{
    public:
    void handle(sf::Event event) override;
    void update(sf::Time delta, std::vector<GameObject*>& new_objects) override;
    void render(sf::RenderWindow& window) override;
    Player(sf::Vector2f init_pos);

    private:
    float speed;
    sf::Texture texture;

};
class Asteroid: public GameObject
{
    public:
    void handle(sf::Event event) override;
    void update(sf::Time delta, std::vector<GameObject*>& new_objects) override;
    void render(sf::RenderWindow& window) override;
    private:
    float proj_speed;
    
};
class Projectile: public GameObject
{
    public:
    Projectile(sf::Vector2f init_pos, std::string init_dir);

    void handle(sf::Event event) override;
    void update(sf::Time delta, std::vector<GameObject*>& new_objects) override;
    void render(sf::RenderWindow& window) override;
    private:
    std::string dir;
    sf::RectangleShape shape;
    float proj_speed;
    sf::Vector2i proj_size;
};