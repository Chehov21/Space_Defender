#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include"Bullet.h"
#include"Enemy.h"
#include"Button.h"
#include"Gain.h"
#define PI 3.14159265

class Player : public sf::Drawable, public sf::Transformable
{
public:

    Player();

    bool load(const std::string& tileset, unsigned int width, unsigned int height);

    void rotate(sf::Vector2i mouse, sf::Vector2f startPosition);

    void shoot(sf::Vector2f start, sf::Vector2i end, std::vector<Bullet>& vec);

    void shoot(sf::Vector2f start, sf::Vector2i end, std::vector<Bullet>& vec, int oneToThree);

    sf::ConvexShape getModel();

    int getScore(int count);

    int getHighscore(int score);

    float getAngle();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float m_angle=0;
    int m_score = 0;
    int m_highscore = 0;
    sf::Texture m_texture;
    sf::ConvexShape m_model;
};

bool isCoolision(std::vector<Enemy>& vec, Player& ship, sf::RenderWindow& window);

void isCoolision(std::vector<Enemy>& vec_e, std::vector<Bullet>& vec_b, Player& ship, sf::RenderWindow& window);

bool isCoolision(std::vector<Gain>& vec_g, std::vector<Bullet>& vec_b, Player& ship, sf::RenderWindow& window);