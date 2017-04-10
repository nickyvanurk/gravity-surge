#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class UIElement
{
public:
	UIElement(const int number, sf::Font& font, bool isActive);

	void draw(sf::RenderWindow& window);

	void updateActive();

	void			setActive(bool isActive);
	bool			getActive();

	void			setPosition(float x, float y);
	sf::Vector2f	getPosition();

	void			setSize(int x, int y);
	sf::Vector2f	getSize();

	int getValue();

private:
	sf::Text			m_text;
	sf::RectangleShape	m_rectangle;
	int					m_value;
	bool				m_active;
};

#endif // !UIELEMENT_HPP