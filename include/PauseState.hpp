#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class PauseState : public State
{
public:
	PauseState(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update(const sf::Time& dt);
	void draw();

	void createButton(float x, float y, sf::Texture& bg, sf::Text& title);
	void freeMemory();

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	sf::Texture m_pausedTex;
	sf::Sprite m_paused;

	sf::Texture m_buttonTex;

	sf::Font m_font;
	sf::Text m_continue;
	sf::Text m_exit;

	sf::Texture m_cursorTex;
	sf::Sprite m_cursor;

	std::vector<std::unique_ptr<sf::Sprite>> m_buttons;

	sf::Vector2i m_mousePosition;
};

#endif // !PAUSESTATE_HPP