#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<vector>
#include"CArray.h"
#define PI 3.14159265

class Bullet
{
public:

    // startPosition- это позиция на конце ракеты, а imaginaryStartPosition это центр ракеты (пофикшен баг с неправильным направлением полета пули)
    Bullet(const sf::Vector2f& StartPosition = sf::Vector2f(0, 0), const sf::Vector2f& imaginaryStartPosition = sf::Vector2f(0, 0),const sf::Vector2i& endPosition = sf::Vector2i(0, 0));

    Bullet(const sf::Vector2f& StartPosition, const sf::Vector2f& imaginaryStartPosition, const sf::Vector2i& endPosition, int oneToThree);

    void setX(float x);

    void setY(float y);

    float getX();

    float getY();

    float getAngle();

    int getOneToThree()
    {
        return m_oneToThree;
    }

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f position);

    sf::CircleShape getBullet();

private:

    sf::CircleShape m_bullet;
    sf::Vector2f m_position;
    float m_angle;
    int m_oneToThree = 0;
};

void moveBullets(CArray<Bullet>& arr, sf::RenderWindow& window);

sf::Vector2f trajectory(float angle);

