#pragma comment(lib, "OpenGL32.lib")
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Palyer.h"
#include"Enemy.h"
#include"Bullet.h"
#include"Button.h"

#define PI 3.14159265

int main()
{
    // Time
    srand(time(0));
    sf::Clock clock;
    float spawnTime = 0;

    // Ship
    Player ship;
    sf::Vector2f startPosition = sf::Vector2f(520.0f, 370.0f);
    ship.setPosition(startPosition);

    // Кнопки Да/Нет
    Button buttontryAgain(sf::Vector2f(420.f, 550.f), sf::Vector2f(80.f, 30.f));
    Button buttonEnd(sf::Vector2f(550.f, 550.f), sf::Vector2f(80.f, 30.f));

    // Background
    sf::Sprite background;
    sf::Texture spaceBackground;
    if (!spaceBackground.loadFromFile("spaceBackground.jpg"))
        return -1;
    background.setTexture(spaceBackground);

    // Text
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text scoreOut;
    scoreOut.setFillColor(sf::Color::White);
    scoreOut.setCharacterSize(20);
    scoreOut.setFont(font);
    scoreOut.setPosition(200.f, 50.f);

    sf::Text highScoreOut;
    highScoreOut.setFillColor(sf::Color::White);
    highScoreOut.setCharacterSize(20);
    highScoreOut.setFont(font);
    highScoreOut.setPosition(300.f, 50.f);

    // Надпись LOSE
    sf::Text Lose;
    Lose.setFillColor(sf::Color::White);
    Lose.setCharacterSize(50);
    Lose.setFont(font);
    Lose.setPosition(450.f, 180.f);
    Lose.setString("LOSE!");

    // Надпись Try again
    sf::Text tryAgain;
    tryAgain.setFillColor(sf::Color::White);
    tryAgain.setCharacterSize(50);
    tryAgain.setFont(font);
    tryAgain.setPosition(410.f, 440.f);
    tryAgain.setString("Try again?");

    // Надпись Yes
    sf::Text Yes;
    Yes.setFillColor(sf::Color::White);
    Yes.setCharacterSize(15);
    Yes.setFont(font);
    Yes.setPosition(450.f, 555.f);
    Yes.setString("Yes");

    // Надпись No
    sf::Text No;
    No.setFillColor(sf::Color::White);
    No.setCharacterSize(15);
    No.setFont(font);
    No.setPosition(580.f, 555.f);
    No.setString("No");

    // Bullets
    std::vector <Bullet> bullets;

    // Enemies
    std::vector <Enemy> enemies;

    // Window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Window", sf::Style::Default);
    window.setFramerateLimit(60);

    // End?
    bool end = false;

    while (window.isOpen())
    {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        std::ostringstream score;
        std::ostringstream highScore;
        sf::Event event;

        // Проигрыш
        if (end==true)
        {

            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // Продолжение игры
                        if (buttontryAgain.isButtonClick(sf::Mouse::getPosition(window)))
                        {
                                end = false;
                                std::vector<Enemy>().swap(enemies);
                                std::vector<Bullet>().swap(bullets);
                                spawnTime = 0;
                                ship.getHighscore(ship.getScore(0));
                                ship.getScore(-ship.getScore(0));
                        }

                        // Endgame
                        if (buttonEnd.isButtonClick(sf::Mouse::getPosition(window)))
                        {
                            return 0;
                        }
                    }
                default:
                    break;
                }
            }

            // Отрисовка фона
            window.draw(background);

            // Отрисовка корабля
            window.draw(ship);

            // Отрисовка score
            score << ship.getScore(0);
            scoreOut.setString("Score=" + score.str());
            window.draw(scoreOut); 

            // Отрисовка highscore
            highScore << ship.getHighscore(0);
            highScoreOut.setString("Highscore=" + highScore.str());
            window.draw(highScoreOut);

            // Отрисовка кнопок
            window.draw(buttontryAgain.getButton());
            window.draw(buttonEnd.getButton());

            // Отрисовка текста
            window.draw(Lose);
            window.draw(tryAgain);
            window.draw(Yes);
            window.draw(No);
            /*std::cout << "  x  " << mouse.x << std::endl;
            std::cout << "  y  " << mouse.y << std::endl;
            std::cout << "  angle=" << ship.getAngle() << std::endl;
            std::cout << "--------" << std::endl;
            std::cout << "--------" << std::endl;*/
        }
        else
        {
            float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
            clock.restart(); //перезагружает время
            sf::Time t1 = sf::microseconds(10000);

            // Вращение корабля
            ship.rotate(mouse, startPosition);
            window.clear();

            while (window.pollEvent(event))
            {
                // Обработка событий
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        ship.shoot(sf::Vector2f((520.f - 520.f) * cos((ship.getAngle() + 90) * PI / 180) - (315.f - 370.f) * sin((ship.getAngle() + 90) * PI / 180) + 520.f,
                            (520.f - 520.f) * sin((ship.getAngle() + 90) * PI / 180) + (315.f - 370.f) * cos((ship.getAngle() + 90) * PI / 180) + 370.f), mouse, bullets);
                    }
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        ship.shoot(sf::Vector2f((520.f - 520.f) * cos((ship.getAngle() + 90) * PI / 180) - (315.f - 370.f) * sin((ship.getAngle() + 90) * PI / 180) + 520.f,
                            (520.f - 520.f) * sin((ship.getAngle() + 90) * PI / 180) + (315.f - 370.f) * cos((ship.getAngle() + 90) * PI / 180) + 370.f), mouse, bullets);
                    }
                    break;

                default:
                    break;
                }
            }

            /*std::cout << "  x  " << mouse.x << std::endl;
            std::cout << "  y  " << mouse.y << std::endl;
            std::cout << "  angle=" << ship.getAngle() << std::endl;
            std::cout << "--------" << std::endl;
            std::cout << "--------" << std::endl;*/

            // Спавн врагов
            spawnTime += time;
            IsSpawnEnemy(spawnTime, startPosition, enemies);

            // Отрисовка фона
            window.draw(background);

            // Движение пуль
            moveBullets(bullets, window);

            // Движение врагов
            moveEnemies(enemies, window);

            // Проверка на столкновение
            end = isCoolision(bullets, enemies, ship, window);

            // Отрисовка корабля
            window.draw(ship);

            // Отрисовка score
            score << ship.getScore(0);
            scoreOut.setString("Score=" + score.str());
            window.draw(scoreOut);

            // Отрисовка highscore
            highScore << ship.getHighscore(0);
            highScoreOut.setString("Highscore=" + highScore.str());
            window.draw(highScoreOut);
        }
        // end the current frame
        window.display();
    }
    return 0;
}