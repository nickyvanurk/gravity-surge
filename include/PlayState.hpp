#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.hpp"
#include "Planet.hpp"
#include "Player.hpp"
#include "Wormhole.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class PlayState : public State
{
public:
	PlayState(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update(const sf::Time& dt);
	void draw();

	void processInput();

private:
	sf::Texture		m_bgTex;
	sf::Texture		m_playerTex;
	sf::Texture		m_moonTex;
	sf::Texture		m_planetTex;
	sf::Texture		m_sunTex;
	sf::Texture     m_blackHoleTex;
	sf::Texture		m_wormholeTex;
	sf::Sprite		m_bg;

	sf::Texture m_cursorTex;
	sf::Sprite m_cursor;

	std::vector<Planet> m_planets;

	Player			m_ship;
	Wormhole		m_wormhole;

	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_triesText;

	int				m_tries;
	float			m_lineLength;
	sf::Vector2i	m_mousePosition;

	bool			m_leftMouseDown;
	bool			m_mouseHoverPlayer;
};

#endif // !PLAYSTATE_HPP