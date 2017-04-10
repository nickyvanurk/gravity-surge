#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

class MenuState : public State
{
public:
	MenuState(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update(const sf::Time& dt);	
	void draw();

	void createButton(float x, float y, sf::Texture& bg, sf::Text& title);
	void freeMemory();

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	sf::Texture m_buttonTex;

	sf::Texture m_cursorTex;
	sf::Sprite m_cursor;

	sf::Font m_font;
	sf::Text m_startText;
	sf::Text m_howtoText;
	sf::Text m_creditsText;
	sf::Text m_exitText;

	std::vector<std::unique_ptr<sf::Sprite>> m_buttons;

	sf::Vector2i m_mousePosition;
};

#endif // !MENUSTATE_HPP