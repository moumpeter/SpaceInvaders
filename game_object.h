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
    void collides(GameObject* game_object);
    sf::FloatRect get_bounds(); 
    void update_dead(bool var);

    protected:
    sf::Vector2f pos;
    sf::Sprite sprite;
    float speed;
    bool dead;
    sf::Texture texture;

};

class Enemy : public GameObject
{
    public:
    Enemy(sf::Vector2f init_pos);
    void handle(sf::Event event) override;
    void update(sf::Time delta, std::vector<GameObject*>& new_objects) override;
    void render(sf::RenderWindow& window) override;
    void direction(std::string dir);
    sf::FloatRect get_bounds();
    
    //bool collides() override;
    private:
    float speed;
    float timer;
    float dir;
    
    
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
   


};
class Asteroid: public GameObject
{
    public:
    void handle(sf::Event event) override;
    void update(sf::Time delta, std::vector<GameObject*>& new_objects) override;
    void render(sf::RenderWindow& window) override;
    Asteroid(sf::Vector2f init_pos, sf::Texture init_texture);

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
    float proj_speed;
    sf::Vector2f proj_size;
};