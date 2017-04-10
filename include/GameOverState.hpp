#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class GameOverState : public State
{
public:
	GameOverState(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update(const sf::Time& dt);
	void draw();

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	sf::Texture m_buttonTex;
	sf::Sprite m_button;

	sf::Texture m_congratsTex;
	sf::Sprite m_congrats;

	sf::Texture m_cursorTex;
	sf::Sprite m_cursor;

	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_continue;

	sf::Vector2i m_mousePosition;
};

#endif // !GAMEOVERSTATE_HPP