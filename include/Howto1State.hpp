#ifndef HOWTO1STATE_HPP
#define HOWTO1STATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Howto1State : public State
{
public:
	Howto1State(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update(const sf::Time& dt);
	void draw();

	void createButton(float x, float y, sf::Texture& bg, bool flip);
	void freeMemory();

private:
	sf::Texture m_bgTex;
	sf::Texture m_buttonTex;
	sf::Texture	m_playerTex;
	sf::Texture	m_planetsTex;
	sf::Texture	m_wormholeTex;

	sf::Sprite m_bg;
	sf::Sprite m_playerImg;
	sf::Sprite m_planetsImg;
	sf::Sprite m_wormholeImg;

	sf::Font m_font;
	sf::Text m_textPlayer;
	sf::Text m_textPlanets;
	sf::Text m_textWormhole;

	sf::Texture m_cursorTex;
	sf::Sprite m_cursor;

	std::vector<std::unique_ptr<sf::Sprite>> m_buttons;

	sf::Vector2i m_mousePosition;
};

#endif // !HOWTO1STATE_HPP