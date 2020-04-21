#include"Enemy.h"

Enemy::Enemy(const sf::Vector2f StartPosition)
{
    sf::Vector2f startPosition = sf::Vector2f(abs(rand() % 1024), abs(rand() % 768));
    while (startPosition.x > 250.f && startPosition.y > 165.f && startPosition.y < 580.f && startPosition.x < 830.f && startPosition.y < 580.f)
    {
        startPosition = sf::Vector2f(abs(rand() % 1024), abs(rand() % 768));
    }
    sf::Vector2f endPosition = StartPosition;
    m_enemy.setRadius(10.f);
    m_enemy.setFillColor(sf::Color::Red);
    m_position = startPosition;
    m_angle = atan((startPosition.y - endPosition.y) / (startPosition.x - endPosition.x)) * 180.0 / PI;
    if ((endPosition.x < startPosition.x && endPosition.y < startPosition.y) || (endPosition.x < startPosition.x && endPosition.y > startPosition.y))
    {
        m_angle += 180;
    }
    m_enemy.setPosition(startPosition);
}

void Enemy::setX(float x)
{
    m_position.x = x;
}

void Enemy::setY(float y)
{
    m_position.y = y;
}

float Enemy::getX()
{
    return m_position.x;
}

float Enemy::getY()
{
    return m_position.y;
}

float Enemy::getAngle()
{
    return m_angle;
}

sf::Vector2f Enemy::getPosition()
{
    return m_position;
}

void Enemy::setPosition(sf::Vector2f position)
{
    m_position = position;
    m_enemy.setPosition(m_position);
}

sf::CircleShape Enemy::getEnemy()
{
    return m_enemy;
}

void moveEnemies(CArray <Enemy>& arr, sf::RenderWindow &window)
{
    int count_e = 0;
    for(int i=0;i<arr.size();i++)
    {
        arr[i].setX(arr[i].getX() + cos(arr[i].getAngle() * PI / 180) * 2);
        arr[i].setY(arr[i].getY() + sin(arr[i].getAngle() * PI / 180) * 2);
        arr[i].setPosition(arr[i].getPosition());
        window.draw(arr[i].getEnemy());
        if (arr[i].getX() > 1024 || arr[i].getX() < 0 || arr[i].getY() > 768 || arr[i].getY() < 0)
        {
            arr.erase(count_e);
            if (arr.size()==0)
            {
                // Освобождение памяти
                arr.clear();
            }
        }
        count_e++;
    }
}

void IsSpawnEnemy(float &spawnEnemyTime, sf::Vector2f &startPosition, CArray<Enemy>& arr)
{
    if (spawnEnemyTime > 1000000)
    {
        Enemy enemy(startPosition);
        arr.push_back(enemy);
        spawnEnemyTime = 0;
    }
}
