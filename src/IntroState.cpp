#include "IntroState.hpp"
#include "StateManager.hpp"
#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

IntroState::IntroState(StateManager& stateManager, sf::RenderWindow& window, bool replace)
	: State{ stateManager, window, replace }
	, m_fade{ true }
{
	m_bgTex.loadFromFile("Assets/Textures/bg.png");
	m_bg.setTexture(m_bgTex);

	// Tile the background
	m_bgTex.setRepeated(true);
	m_bg.setTextureRect(sf::IntRect{ 0, 0, APP_WIDTH, APP_HEIGHT });

	m_logoTex.loadFromFile("Assets/Textures/Menu/logo.png");
	m_logo.setTexture(m_logoTex, true);

	m_logo.setPosition(APP_WIDTH / 2 - m_logo.getLocalBounds().width / 2,
		               APP_HEIGHT / 2 - m_logo.getLocalBounds().height / 2);

	m_font.loadFromFile("Assets/Fonts/HelveticaLTStd-Roman.otf");
	m_text.setFont(m_font);

	m_text.setString("Press [SPACEBAR] to continue");
	m_text.setCharacterSize(12);
	m_text.setColor(sf::Color{ 89, 106, 209, 255 });

	// Cast to int to prevent blurry text
	m_text.setPosition(static_cast<int>(APP_WIDTH / 2 - m_text.getLocalBounds().width / 2),
					   static_cast<int>(APP_HEIGHT / 2 - m_text.getLocalBounds().height / 2 + 150));

	m_alphaText = sf::Color{ 89, 106, 209, 255 };
	m_alphaRect = sf::Color{ 0, 0, 0, 255 };

	// Fill the fader surface with black
	m_fader.setFillColor(m_alphaRect);
	m_fader.setSize(sf::Vector2f(APP_WIDTH, APP_HEIGHT));

	std::cout << "IntroState Init" << std::endl;
}

void IntroState::pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void IntroState::resume()
{
	std::cout << "IntroState Resume" << std::endl;
}

void IntroState::update(const sf::Time& dt)
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_stateManager.quit();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				m_next = StateManager::build<MenuState>(m_stateManager, m_window, true);
				break;

			case sf::Keyboard::Escape:
				m_stateManager.quit();
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	// When to fade in/out
	if (m_alphaText.a <= 0)
		m_fade = false;
	else if (m_alphaText.a >= 255)
		m_fade = true;

	// The actual fading
	if (m_fade)
		m_alphaText.a -= 5;
	else
		m_alphaText.a += 5;


	if (m_alphaRect.a != 0)
		m_alphaRect.a -= 5;

	m_text.setColor(m_alphaText);
	m_fader.setFillColor(m_alphaRect);
}

void IntroState::draw()
{
	m_window.clear();

	m_window.draw(m_bg);
	m_window.draw(m_logo);
	m_window.draw(m_text);

	// No need to draw if it's transparent
	if (m_alphaRect.a != 0)
		m_window.draw(m_fader);

	m_window.display();
}