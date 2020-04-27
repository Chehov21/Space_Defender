#include"Bullet.h"

Bullet::Bullet(const sf::Vector2f& StartPosition, const sf::Vector2f& imaginaryStartPosition, const sf::Vector2i& endPosition)
{
    m_bullet.setRadius(5.f);
    m_bullet.setFillColor(sf::Color::White);
    m_position.x = StartPosition.x;
    m_position.y = StartPosition.y;
    m_angle = atan((endPosition.y - imaginaryStartPosition.y) / (endPosition.x - imaginaryStartPosition.x)) * 180.0 / PI;
    if ((endPosition.x < imaginaryStartPosition.x && endPosition.y < imaginaryStartPosition.y) || (endPosition.x < imaginaryStartPosition.x && endPosition.y > imaginaryStartPosition.y))
    {
        m_angle += 180;
    }
    //std::cout << "endX= " << endPosition.x << " endY=" << endPosition.y << std::endl;
    m_bullet.setPosition(StartPosition);
}

Bullet::Bullet(const sf::Vector2f& StartPosition, const sf::Vector2f& imaginaryStartPosition, const sf::Vector2i& endPosition, int oneToThree)
{
    if (oneToThree == 40)
    {
        m_oneToThree = 40;
    }
    else m_oneToThree = -40;
    m_bullet.setRadius(5.f);
    m_bullet.setFillColor(sf::Color::White);
    m_position.x = StartPosition.x;
    m_position.y = StartPosition.y;
    m_angle = atan((endPosition.y - imaginaryStartPosition.y) / (endPosition.x - imaginaryStartPosition.x)) * 180.0 / PI;
    if ((endPosition.x < imaginaryStartPosition.x && endPosition.y < imaginaryStartPosition.y) || (endPosition.x < imaginaryStartPosition.x && endPosition.y > imaginaryStartPosition.y))
    {
        m_angle += 180;
    }
    //std::cout << "endX= " << endPosition.x << " endY=" << endPosition.y << std::endl;
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

void moveBullets(CArray<Bullet>& arr, sf::RenderWindow& window)
{
    int count_b = 0;
    for (int i=0;i<arr.size();i++)
    {
        if (arr[i].getOneToThree() == 40)
        {
            arr[i].setX(arr[i].getX() + cos(arr[i].getAngle() * PI / 180 + 40) + cos(arr[i].getAngle() * PI / 180) * 5);
            arr[i].setY(arr[i].getY() + sin(arr[i].getAngle() * PI / 180 + 40) + sin(arr[i].getAngle() * PI / 180) * 5);
            arr[i].setPosition(arr[i].getPosition());
            window.draw(arr[i].getBullet());
            if (arr[i].getX() > 1024 || arr[i].getX() < 0 || arr[i].getY() > 768 || arr[i].getY() < 0)
            {
                arr.erase(count_b);
                count_b--;
                i--;
                int size = arr.size();
                if (size == 0)
                {
                    // Освобождение памяти
                    arr.clear();
                }
            }
            count_b++;
        }
        else if (arr[i].getOneToThree() == -40)
        {
            arr[i].setX(arr[i].getX() + cos(arr[i].getAngle() * PI / 180 - 40) + cos(arr[i].getAngle() * PI / 180) * 5);
            arr[i].setY(arr[i].getY() + sin(arr[i].getAngle() * PI / 180 - 40) + sin(arr[i].getAngle() * PI / 180) * 5);
            arr[i].setPosition(arr[i].getPosition());
            window.draw(arr[i].getBullet());
            if (arr[i].getX() > 1024 || arr[i].getX() < 0 || arr[i].getY() > 768 || arr[i].getY() < 0)
            {
                arr.erase(count_b);
                count_b--;
                i--;
                int size = arr.size();
                if (size == 0)
                {
                    // Освобождение памяти
                    arr.clear();
                }
            }
            count_b++;
        }
        else
        {
            arr[i].setX(arr[i].getX() + cos(arr[i].getAngle() * PI / 180) * 5);
            arr[i].setY(arr[i].getY() + sin(arr[i].getAngle() * PI / 180) * 5);
            arr[i].setPosition(arr[i].getPosition());
            window.draw(arr[i].getBullet());
            if (arr[i].getX() > 1024 || arr[i].getX() < 0 || arr[i].getY() > 768 || arr[i].getY() < 0)
            {
                arr.erase(count_b);
                count_b--;
                i--;
                int size = arr.size();
                if (size == 0)
                {
                    // Освобождение памяти
                    arr.clear();
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
