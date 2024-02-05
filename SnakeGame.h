#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <SFML/Graphics.hpp>
#include "Snake.h"

class SnakeGame : public sf::Drawable, public sf::Updateable {
public:
    SnakeGame();
    ~SnakeGame();
    void Run();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void update(sf::Time deltaTime) override;

    void HandleInput();
    void SpawnFood();
    bool IsCollidingWithSelf() const;
    bool IsCollidingWithWall() const;
    bool IsCollidingWithFood() const;

    sf::RenderWindow m_window;
    Snake m_snake;
    sf::RectangleShape m_food;
    sf::Time m_snakeSpeed;
    sf::Vector2i m_snakeDirection;
};

#endif // SNAKE_GAME_H
