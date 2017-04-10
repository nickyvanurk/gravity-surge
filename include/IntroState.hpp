#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class IntroState : public State
{
public:
	IntroState(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update(const sf::Time& dt);
	void draw();

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	sf::Texture m_logoTex;
	sf::Sprite m_logo;

	sf::Font m_font;
	sf::Text m_text;

	bool m_fade;
	sf::Color m_alphaText;

	sf::RectangleShape m_fader;
	sf::Color m_alphaRect;
};

#endif // !INTROSTATE_HPP