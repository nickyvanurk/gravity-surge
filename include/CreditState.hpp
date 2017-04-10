#ifndef CREDITSTATE_HPP
#define CREDITSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class CreditState : public State
{
public:
	CreditState(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

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

	sf::Vector2i m_mousePosition;
};

#endif // !CREDITSTATE_HPP