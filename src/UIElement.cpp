#include "UIElement.hpp"
#include "Constants.hpp"

UIElement::UIElement(const int number, sf::Font& font, bool isActive)
{
	m_active = isActive;
	m_value = number;

	setSize(((APP_WIDTH - 20) - 50) / 6, (((APP_HEIGHT - 20) - 40) / 5) - 10);
	m_rectangle.setOrigin(m_rectangle.getGlobalBounds().width / 2, m_rectangle.getGlobalBounds().height / 2);
	m_rectangle.setOutlineThickness(-5);

	m_text.setString(std::to_string(number));
	m_text.setFont(font);
	m_text.setCharacterSize(32);

	updateActive();
}

void UIElement::updateActive()
{
	if (m_active)
	{
		m_rectangle.setFillColor(sf::Color(0, 0, 0, 0));
		m_rectangle.setOutlineColor(sf::Color::White);
		m_text.setColor(sf::Color::White);
	}
	else
	{
		m_rectangle.setFillColor(sf::Color(0, 0, 0, 255));
		m_rectangle.setOutlineColor(sf::Color(50, 50, 50, 255));
		m_text.setColor(sf::Color(0, 0, 0, 255));
	}
}

void UIElement::setPosition(float x, float y)
{
	m_rectangle.setPosition(x + m_rectangle.getGlobalBounds().width / 2, y + m_rectangle.getGlobalBounds().height / 2);
	m_text.setPosition(m_rectangle.getPosition().x - m_text.getGlobalBounds().width / 2,
		m_rectangle.getPosition().y - m_text.getGlobalBounds().height);
}

void UIElement::draw(sf::RenderWindow& window)
{
	window.draw(m_rectangle);
	window.draw(m_text);
}

sf::Vector2f UIElement::getPosition()
{
	return m_rectangle.getPosition() - m_rectangle.getOrigin();
}

int UIElement::getValue()
{
	return m_value;
}

void UIElement::setActive(bool isActive)
{
	m_active = isActive;
}

bool  UIElement::getActive()
{
	return m_active;
}

void UIElement::setSize(int x, int y)
{
	m_rectangle.setSize(sf::Vector2f(x, y));
}

sf::Vector2f UIElement::getSize()
{
	return m_rectangle.getSize();
}