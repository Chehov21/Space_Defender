#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<vector>
#include"CArray.h"
#define PI 3.14159265

class Enemy
{
public:

    Enemy(const sf::Vector2f StartPosition = sf::Vector2f(0, 0));

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

void moveEnemies(CArray <Enemy>& arr, sf::RenderWindow& window);

void IsSpawnEnemy(float& spawnEnemyTime, sf::Vector2f& startPosition, CArray<Enemy>& arr);