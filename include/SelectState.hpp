#ifndef SELECTSTATE_HPP
#define SELECTSTATE_HPP

#include "State.hpp"
#include "UIElement.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

class SelectState : public State
{
public:
	SelectState(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update(const sf::Time& dt);
	void draw();

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	sf::Texture m_buttonTex;
	sf::Sprite m_button;

	sf::Texture m_cursorTex;
	sf::Sprite m_cursor;

	sf::Font m_font;
	sf::Text m_text;

	std::vector<UIElement> m_buttons;

	sf::Vector2i m_mousePosition;
};

#endif // !SELECTSTATE_HPP