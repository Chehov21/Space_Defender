#include "Gain.h"

Gain::Gain()
{
    sf::Vector2f Position = sf::Vector2f(abs(rand() % 1024), abs(rand() % 768));
    while (Position.x > 250.f && Position.y > 165.f && Position.y < 580.f && Position.x < 830.f && Position.y < 580.f)
    {
        Position = sf::Vector2f(abs(rand() % 1024), abs(rand() % 768));
    }
    m_gain.setRadius(m_radius);
    m_gain.setFillColor(sf::Color::Green);
    m_position = Position;
    m_gain.setOrigin(m_radius, m_radius);
    m_gain.setPosition(m_position);
    std::cout << "x= " << Position.x << "y= " << Position.y << std::endl;
}

void Gain::setX(float x)
{
    m_position.x = x;
}

void Gain::setY(float y)
{
    m_position.y = y;
}

float Gain::getX()
{
    return m_position.x;
}

float Gain::getY()
{
    return m_position.y;
}

sf::Vector2f Gain::getPosition()
{
    return m_position;
}

void Gain::setPosition(sf::Vector2f position)
{
    m_position = position;
    m_gain.setPosition(m_position);
}

sf::CircleShape Gain::getGain()
{
    return m_gain;
}

float Gain::getRadius()
{
    return m_radius;
}

// Ошибка в ситуации, когда первый шар исчез, а второй все еще рисуется
void Gain::increaseRadius()
{
    m_gain.setOrigin(m_radius, m_radius);
    m_radius = m_radius - 0.1;
    m_gain.setRadius(m_radius);
}

// Уменьшение размера шара с усилением
void increaseSize(std::vector<Gain>& vec, sf::RenderWindow& window)
{
    int count_g = 0;
    for (Gain& g : vec)
    {
        window.draw(g.getGain());
        std::cout << "R= " << g.getRadius() << std::endl;
        if ((g.getRadius() - 0.1) > 0) {
            g.increaseRadius();
        }
        else
        {
            vec.erase(vec.begin() + count_g);
        }
        if (vec.size() == 0)
        {
            // Освобождение памяти
            std::vector<Gain>().swap(vec);
        }
        count_g++;
    }
}

sf::Vector2i oneToThree(sf::Vector2f startPosition, sf::Vector2i endPosition, float angle)
{
    float rx = 0;
    float ry = 0;
    float R = 0;
    if ((endPosition.x < startPosition.x && endPosition.y <= startPosition.y) || (endPosition.x < startPosition.x && endPosition.y > startPosition.y))
    {
        angle += 180;
    }
    if (startPosition.x == endPosition.x)
    {
        R = endPosition.y - startPosition.y;
    }
    if (startPosition.y = endPosition.y)
    {
        R = endPosition.x - startPosition.x;
    }
    else {
        R = sqrt(pow((endPosition.y - startPosition.y), 2) + pow((endPosition.x - startPosition.x), 2));
    }
    return sf::Vector2i(startPosition.x+ R * cos(angle), startPosition.y+ R * sin(angle));
}

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

void IsSpawnGain(float& spawnGainTime, std::vector<Gain>& vec)
{
    if (spawnGainTime > 5000000)
    {
        Gain gain;
        vec.push_back(gain);
        spawnGainTime = 0;
    }
}
