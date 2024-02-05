#include "Snake.h"

Snake::Snake(int startX, int startY) {
    m_segments.push_back({ sf::Vector2i(startX, startY), sf::RectangleShape(sf::Vector2f(10, 10)) });
    m_segments.back().shape.setFillColor(sf::Color::Green);
}

Snake::~Snake() {
}

void Snake::Move(const sf::Vector2i& direction) {
    for (int i = m_segments.size() - 1; i > 0; --i) {
        m_segments[i].position = m_segments[i - 1].position;
    }
    m_segments[0].position += direction;
}

void Snake::Grow() {
    Segment newSegment = m_segments.back();
    newSegment.position = m_segments[m_segments.size() - 2].position;
    m_segments.push_back(newSegment);
}

sf::FloatRect Snake::GetHeadPosition() const {
    return sf::FloatRect(m_segments[0].position * 10.f, sf::Vector2f(10, 10));
}

int Snake::GetLength() const {
    return m_segments.size();
}

void Snake::Draw(sf::RenderWindow& window) {
    for (const auto& segment : m_segments) {
        window.draw(segment.shape);
    }
}
