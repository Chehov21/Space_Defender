#include"Bullet.h"

Bullet::Bullet(sf::Vector2f& StartPosition, sf::Vector2i& endPosition)
{
    m_bullet.setRadius(5.f);
    m_bullet.setFillColor(sf::Color::White);
    m_position.x = StartPosition.x;
    m_position.y = StartPosition.y;
    m_angle = atan((endPosition.y - StartPosition.y) / (endPosition.x - StartPosition.x)) * 180.0 / PI;
    if ((endPosition.x < StartPosition.x && endPosition.y < StartPosition.y) || (endPosition.x < StartPosition.x && endPosition.y > StartPosition.y))
    {
        m_angle += 180;
    }
    m_bullet.setPosition(StartPosition);
}

void Bullet::setX(float x)
{
    m_position.x = x;
}

void Bullet::setY(float y)
{
    m_position.y = y;
}

float Bullet::getX()
{
    return m_position.x;
}

float Bullet::getY()
{
    return m_position.y;
}

float Bullet::getAngle()
{
    return m_angle;
}

sf::Vector2f Bullet::getPosition()
{
    return m_position;
}

void Bullet::setPosition(sf::Vector2f position)
{
    m_position = position;
    m_bullet.setPosition(m_position);
}

sf::CircleShape Bullet::getBullet()
{
    return m_bullet;
}

void moveBullets(std::vector<Bullet>& vec, sf::RenderWindow& window)
{
    int count_b = 0;
    for (Bullet& b : vec)
    {
        b.setX(b.getX() + cos(b.getAngle() * PI / 180) * 5);
        b.setY(b.getY() + sin(b.getAngle() * PI / 180) * 5);
        b.setPosition(b.getPosition());
        window.draw(b.getBullet());
        if (b.getX() > 1024 || b.getX() < 0 || b.getY() > 768 || b.getY() < 0)
        {
            vec.erase(vec.begin() + count_b);
            int size = vec.size();
            if (size == 0)
            {
                // Освобождение памяти
                std::vector<Bullet>().swap(vec);
            }
        }
        count_b++;
    }
}
