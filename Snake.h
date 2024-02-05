#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Snake {
public:
    Snake(int startX, int startY);
    ~Snake();
    void Move(const sf::Vector2i& direction);
    void Grow();
    sf::FloatRect GetHeadPosition() const;
    int GetLength() const;
    void Draw(sf::RenderWindow& window);

private:
    struct Segment {
        sf::Vector2i position;
        sf::RectangleShape shape;
    };
    std::vector<Segment> m_segments;
};

#endif // SNAKE_H
