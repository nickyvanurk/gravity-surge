#ifndef HOWTO2STATE_HPP
#define HOWTO2STATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Howto2State : public State
{
public:
	Howto2State(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update(const sf::Time& dt);
	void draw();

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	sf::Texture m_buttonTex;
	sf::Sprite m_button;

	sf::Font m_font;
	sf::Text m_text;

	sf::Texture m_cursorTex;
	sf::Sprite m_cursor;

	sf::Vector2i m_mousePosition;
};

#endif // !HOWTO2STATE_HPP