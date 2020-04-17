#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#define PI 3.14159265

class Button
{
public:

	Button(sf::Vector2f position, sf::Vector2f size);
	bool isButtonClick(sf::Vector2i mouse);
	sf::RectangleShape getButton();
private:

	sf::RectangleShape m_button;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
};

