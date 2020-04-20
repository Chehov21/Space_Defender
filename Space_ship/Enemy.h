#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<vector>
#define PI 3.14159265

class Enemy
{
public:

    Enemy(sf::Vector2f StartPosition);

    void setX(float x);

    void setY(float y);

    float getX();

    float getY();

    float getAngle();

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f position);

    sf::CircleShape getEnemy();

private:

    sf::CircleShape m_enemy;
    sf::Vector2f m_position;
    float m_angle;
};

void moveEnemies(std::vector<Enemy>& vec, sf::RenderWindow &window);

void IsSpawnEnemy(float &spawnEnemyTime, sf::Vector2f &startPosition, std::vector<Enemy>& enemies);