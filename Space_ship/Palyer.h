#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include"Bullet.h"
#include"Enemy.h"
#include"Button.h"
#include"Gain.h"
#include"CArray.h"
#include"CArray.h"
#define PI 3.14159265

class Player : public sf::Drawable, public sf::Transformable
{
public:

    Player();

    bool load(const std::string& tileset, unsigned int width, unsigned int height);

    void rotate(sf::Vector2f startPosition, sf::Vector2i mouse);

    void shoot(sf::Vector2f start, sf::Vector2f imaginaryStart, sf::Vector2i end, CArray<Bullet>& arr);

    void shoot(sf::Vector2f start, sf::Vector2f imaginaryStart, sf::Vector2i end, CArray<Bullet>& arr, int oneToThree);

    sf::ConvexShape getModel();

    int getScore(int count);

    int getHighscore(int score);

    float getAngle();

    void setTexture(int count);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float m_angle=0;
    int m_score = 0;
    int m_highscore = 0;
    sf::Texture m_texture;
    sf::ConvexShape m_model;
};

bool isCoolision(CArray <Enemy>& arr, Player& ship, sf::RenderWindow& window);

void isCoolision(CArray<Enemy>& arrE, CArray<Bullet>& arrB, Player& ship, sf::RenderWindow& window);

bool isCoolision(CArray<oneToThree>& arrG, CArray<Bullet>& arrB, sf::RenderWindow& window);

void isCoolision(CArray<Enemy>& arrE, Laser laser, sf::RenderWindow& window);