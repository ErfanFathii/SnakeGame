#include "SnakeGame.h"

SnakeGame::SnakeGame()
    : m_window(sf::VideoMode(640, 480), "Snake Game"),
    m_snakeSpeed(sf::seconds(0.1f)),
    m_snakeDirection(sf::Vector2i(1, 0)) {
    m_window.setFramerateLimit(60);
    SpawnFood();
}

SnakeGame::~SnakeGame() {
}

void SnakeGame::Run() {
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            HandleInput();
        }
        update(sf::seconds(1.0f / 60.0f));
        m_window.clear(sf::Color::Black);
        draw(m_window, sf::RenderStates::Default);
        m_window.display();
    }
}

void SnakeGame::HandleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && m_snakeDirection.x != 1) {
        m_snakeDirection = sf::Vector2i(-1, 0);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && m_snakeDirection.x != -1) {
        m_snakeDirection = sf::Vector2i(1, 0);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_snakeDirection.y != 1) {
        m_snakeDirection = sf::Vector2i(0, -1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_snakeDirection.y != -1) {
        m_snakeDirection = sf::Vector2i(0, 1);
    }
}

void SnakeGame::SpawnFood() {
    m_food.setPosition(rand() % (m_window.getSize().x / 10) * 10, rand() % (m_window.getSize().y / 10) * 10);
    m_food.setSize(sf::Vector2f(10, 10));
    m_food.setFillColor(sf::Color::Red);
}

void SnakeGame::update(sf::Time deltaTime) {
    m_snake.Move(m_snakeDirection);
    if (IsCollidingWithWall() || IsCollidingWithSelf()) {
        m_window.close();
    }
    if (IsCollidingWithFood()) {
        m_snake.Grow();
        SpawnFood();
    }
}

bool SnakeGame::IsCollidingWithSelf() const {
    for (size_t i = 1; i < m_snake.GetLength(); ++i) {
        if (m_snake.GetHeadPosition().intersects(m_snake.GetSegmentPosition(i))) {
            return true;
        }
    }
    return false;
}

bool SnakeGame::IsCollidingWithWall() const {
    sf::FloatRect headPosition = m_snake.GetHeadPosition();
    return headPosition.left < 0 || headPosition.top < 0 || headPosition.left + headPosition.width > m_window.getSize().x || headPosition.top + headPosition.height > m_window.getSize().y;
}

bool SnakeGame::IsCollidingWithFood() const {
    return m_snake.GetHeadPosition().intersects(m_food.getGlobalBounds());
}

void SnakeGame::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_food);
    m_snake.Draw(target);
}
