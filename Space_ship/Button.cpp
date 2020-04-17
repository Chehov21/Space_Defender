#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size)
{
	m_position = position;
	m_size = size;
	m_button.setPosition(position);
	m_button.setSize(size);
	m_button.setOutlineThickness(1.f);
	m_button.setOutlineColor(sf::Color::White);
	m_button.setFillColor(sf::Color::Transparent);
}

bool Button::isButtonClick(sf::Vector2i mouse)
{
	if (mouse.x > m_position.x && mouse.x < (m_position.x + m_size.x) && mouse.y > m_position.y && mouse.y < (m_position.y + m_size.y))
	{
		return true;
	}
	return false;
}

sf::RectangleShape Button::getButton()
{
	return m_button;
}
