#include"Enemy.h"

Enemy::Enemy(sf::Vector2f StartPosition)
{
    sf::Vector2f startPosition = sf::Vector2f(abs(rand() % 1024), abs(rand() % 768));
    while (startPosition.x > 250.f && startPosition.y > 165.f && startPosition.y < 580.f && startPosition.x < 830.f && startPosition.y < 580.f)
    {
        startPosition = sf::Vector2f(abs(rand() % 1024), abs(rand() % 768));
    }
    sf::Vector2f endPosition = StartPosition;
    m_enemy.setRadius(10.f);
    m_enemy.setFillColor(sf::Color::Red);
    m_position.x = startPosition.x;
    m_position.y = startPosition.y;
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

void spawnEnemy(sf::Vector2f start, std::vector<Enemy>& vec)
{
    Enemy enemy(start);
    vec.push_back(enemy);
}

void moveEnemies(std::vector<Enemy>& vec, sf::RenderWindow &window)
{
    int count_e = 0;
    for (Enemy& e : vec)
    {
        e.setX(e.getX() + cos(e.getAngle() * PI / 180) * 2);
        e.setY(e.getY() + sin(e.getAngle() * PI / 180) * 2);
        e.setPosition(e.getPosition());
        window.draw(e.getEnemy());
        if (e.getX() > 1024 || e.getX() < 0 || e.getY() > 768 || e.getY() < 0)
        {
            vec.erase(vec.begin() + count_e);
            int size = vec.size();
            if (size == 0)
            {
                // Освобождение памяти
                std::vector<Enemy>().swap(vec);
            }
        }
        count_e++;
    }
}

void IsSpawnEnemy(float &spawnTime, sf::Vector2f &startPosition, std::vector<Enemy>& enemies)
{
    if (spawnTime > 1000000)
    {
        spawnEnemy(startPosition, enemies);
        spawnTime = 0;
    }
}
