#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<vector>
#include"CArray.h"
#define PI 3.14159265

class Gain
{
public:
    Gain();

    void setX(float x);

    void setY(float y);

    float getX();

    float getY();

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f position);

    sf::CircleShape getGain();

    float getRadius();

    void increaseRadius();

private:
    sf::CircleShape m_gain;
    sf::Vector2f m_position;
    float m_radius=20.f;
};

void IsSpawnGain(float& spawnGainTime, CArray <Gain>& arr);

void increaseSize(CArray <Gain>& arr, sf::RenderWindow& window);

sf::Vector2i oneToThree(sf::Vector2f startPosition, sf::Vector2i endPosition, float angle);