#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<vector>
#define PI 3.14159265

class Bullet
{
public:

    Bullet(sf::Vector2f& StartPosition, sf::Vector2i& endPosition);

    void setX(float x);

    void setY(float y);

    float getX();

    float getY();

    float getAngle();

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f position);

    sf::CircleShape getBullet();

private:

    sf::CircleShape m_bullet;
    sf::Vector2f m_position;
    float m_angle;
};

void moveBullets(std::vector<Bullet>& vec, sf::RenderWindow& window); 