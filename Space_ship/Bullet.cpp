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
    std::cout << "endX= " << endPosition.x << " endY=" << endPosition.y << std::endl;
    m_bullet.setPosition(StartPosition);
}

Bullet::Bullet(sf::Vector2f& StartPosition, sf::Vector2i& endPosition, int oneToThree)
{
    if (oneToThree == 45)
    {
        m_oneToThree = 45;
    }
    else m_oneToThree = -45;
    m_bullet.setRadius(5.f);
    m_bullet.setFillColor(sf::Color::White);
    m_position.x = StartPosition.x;
    m_position.y = StartPosition.y;
    m_angle = atan((endPosition.y - StartPosition.y) / (endPosition.x - StartPosition.x)) * 180.0 / PI;
    if ((endPosition.x < StartPosition.x && endPosition.y < StartPosition.y) || (endPosition.x < StartPosition.x && endPosition.y > StartPosition.y))
    {
        m_angle += 180;
    }
    std::cout << "endX= " << endPosition.x << " endY=" << endPosition.y << std::endl;
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
        if (b.getOneToThree() == 45)
        {
            b.setX(b.getX() + cos(b.getAngle() * PI / 180 + 45) + cos(b.getAngle() * PI / 180) * 5);
            b.setY(b.getY() + sin(b.getAngle() * PI / 180 + 45) + sin(b.getAngle() * PI / 180) * 5);
            b.setPosition(b.getPosition());
            window.draw(b.getBullet());
            if (b.getX() > 1024 || b.getX() < 0 || b.getY() > 768 || b.getY() < 0)
            {
                vec.erase(vec.begin() + count_b);
                int size = vec.size();
                if (size == 0)
                {
                    // Освобождение памяти
                    //std::vector<Bullet>().swap(vec);
                }
            }
            count_b++;
        }
        else if (b.getOneToThree() == -45)
        {
            b.setX(b.getX() + cos(b.getAngle() * PI / 180 - 45) + cos(b.getAngle() * PI / 180) * 5);
            b.setY(b.getY() + sin(b.getAngle() * PI / 180 - 45) + sin(b.getAngle() * PI / 180) * 5);
            b.setPosition(b.getPosition());
            window.draw(b.getBullet());
            if (b.getX() > 1024 || b.getX() < 0 || b.getY() > 768 || b.getY() < 0)
            {
                vec.erase(vec.begin() + count_b);
                int size = vec.size();
                if (size == 0)
                {
                    // Освобождение памяти
                    //std::vector<Bullet>().swap(vec);
                }
            }
            count_b++;
        }
        else
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
                    //std::vector<Bullet>().swap(vec);
                }
            }
            count_b++;
        }
    }
}

sf::Vector2f trajectory(float angle)
{
    return sf::Vector2f((520.f - 520.f) * cos((angle + 90) * PI / 180) - (315.f - 370.f) * sin((angle + 90) * PI / 180) + 520.f,
        (520.f - 520.f) * sin((angle + 90) * PI / 180) + (315.f - 370.f) * cos((angle + 90) * PI / 180) + 370.f);
}
