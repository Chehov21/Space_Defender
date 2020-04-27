#include "Gain.h"

oneToThree::oneToThree()
{
    sf::Vector2f Position = sf::Vector2f(abs(rand() % 1024), abs(rand() % 768));
    while (Position.x > 250.f && Position.y > 165.f && Position.y < 580.f && Position.x < 830.f && Position.y < 580.f)
    {
        Position = sf::Vector2f(abs(rand() % 1024), abs(rand() % 768));
    }
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(sf::Color::Green);
    m_position = Position;
    m_shape.setOrigin(m_radius, m_radius);
    m_shape.setPosition(m_position);
    std::cout << "x= " << Position.x << "y= " << Position.y << std::endl;
}

void oneToThree::setX(float x)
{
    m_position.x = x;
}

void oneToThree::setY(float y)
{
    m_position.y = y;
}

float oneToThree::getX()
{
    return m_position.x;
}

float oneToThree::getY()
{
    return m_position.y;
}

sf::Vector2f oneToThree::getPosition()
{
    return m_position;
}

void oneToThree::setPosition(sf::Vector2f position)
{
    m_position = position;
    m_shape.setPosition(m_position);
}

sf::CircleShape oneToThree::getGain()
{
    return m_shape;
}

float oneToThree::getRadius()
{
    return m_radius;
}

// Ошибка в ситуации, когда первый шар исчез, а второй все еще рисуется
void oneToThree::increaseRadius()
{
    m_shape.setOrigin(m_radius, m_radius);
    m_radius = m_radius - 0.1;
    m_shape.setRadius(m_radius);
}

// Уменьшение размера шара с усилением
void increaseSize(CArray <oneToThree>& arr, sf::RenderWindow& window)
{
    int count_g = 0;
    for(int i=0; i<arr.size();i++)
    {
        window.draw(arr[i].getGain());
        std::cout << "R= " << arr[i].getRadius() << std::endl;
        if ((arr[i].getRadius() - 0.1) > 0) {
            arr[i].increaseRadius();
        }
        else
        {
            arr.erase(count_g);
        }
        if (arr.size() == 0)
        {
            // Освобождение памяти
            arr.clear();
        }
        count_g++;
    }
}

//sf::Vector2i oneToThree(sf::Vector2f startPosition, sf::Vector2i endPosition, float angle)
//{
//    float rx = 0;
//    float ry = 0;
//    float R = 0;
//    if ((endPosition.x < startPosition.x && endPosition.y <= startPosition.y) || (endPosition.x < startPosition.x && endPosition.y > startPosition.y))
//    {
//        angle += 180;
//    }
//    if (startPosition.x == endPosition.x)
//    {
//        R = endPosition.y - startPosition.y;
//    }
//    if (startPosition.y = endPosition.y)
//    {
//        R = endPosition.x - startPosition.x;
//    }
//    else {
//        R = sqrt(pow((endPosition.y - startPosition.y), 2) + pow((endPosition.x - startPosition.x), 2));
//    }
//    return sf::Vector2i(startPosition.x+ R * cos(angle), startPosition.y+ R * sin(angle));
//}

//sf::Vector2i oneToThree(sf::Vector2f startPosition, sf::Vector2i endPosition, float angle)
//{
//    if ((endPosition.x < startPosition.x && endPosition.y <= startPosition.y) || (endPosition.x < startPosition.x && endPosition.y > startPosition.y))
//    {
//        angle += 180;
//    }
//    float rx = 0;
//    float ry = 0;
//    float R = 0;
//    std::cout << "x= " << startPosition.x << "y= " << startPosition.y << std::endl;
//    rx = endPosition.x - startPosition.x;
//    rx = endPosition.y - startPosition.y;
//    return sf::Vector2i(startPosition.x + rx * cos(angle) - ry * sin(angle), startPosition.y + rx * sin(angle) + ry * cos(angle));
//}

void IsSpawnGain(float& spawnGainTime, CArray <oneToThree> & arr)
{
    if (spawnGainTime > 5000000)
    {
        oneToThree gain;
        arr.push_back(gain);
        spawnGainTime = 0;
    }
}

Laser::Laser()
{
    m_laser.setSize(sf::Vector2f(4, 550));
    m_laser.setOrigin(sf::Vector2f(2, 0));
}

sf::RectangleShape Laser::getLaser()
{
    return m_laser;
}

void Laser::rotate(sf::Vector2f startPosition, sf::Vector2i mouse)
{
    m_angle = atan((mouse.y - startPosition.y) / (mouse.x - startPosition.x)) * 180.0 / PI;
    if ((mouse.x < startPosition.x && mouse.y <= startPosition.y) || (mouse.x < startPosition.x && mouse.y > startPosition.y))
    {
        m_angle += 180;
    }
    m_laser.setRotation(m_angle-90);
}

void Laser::setStart(sf::Vector2f startPosition)
{
    m_laser.setPosition(startPosition);
}

