#include "GameOverState.hpp"
#include "StateManager.hpp"
#include "IntroState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

GameOverState::GameOverState(StateManager& stateManager, sf::RenderWindow& window, bool replace)
	: State(stateManager, window, replace)
	, m_mousePosition(0, 0)
{
	// Initialize textures
	m_bgTex.loadFromFile("Assets/Textures/bg.png");
	m_buttonTex.loadFromFile("Assets/Textures/Menu/menuItem.png");
	m_congratsTex.loadFromFile("Assets/Textures/Menu/congratulations.png");

	// Set texture to sprite
	m_bg.setTexture(m_bgTex);
	m_congrats.setTexture(m_congratsTex);

	// Allow the background sprite to repeat itself
	m_bgTex.setRepeated(true);
	m_bg.setTextureRect(sf::IntRect(0, 0, APP_WIDTH, APP_HEIGHT));

	m_congrats.setOrigin(m_congrats.getGlobalBounds().width / 2, m_congrats.getGlobalBounds().height / 2);
	m_congrats.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2 - 100);

	// Load font and set it
	if (!m_font.loadFromFile("Assets/Fonts/HelveticaLTStd-Roman.otf")) std::cout << "Font failed to load.\n" << std::endl;
	m_continue.setFont(m_font);
	m_text.setFont(m_font);

	// Set text strings
	m_continue.setString("Continue");
	m_text.setString("You have just completed the last level of Gravity Surge!\nThanks to you the spaceship managed to return to their\nhome, planet Earth.");
	m_text.setCharacterSize(16);
	m_text.setColor(sf::Color(89, 106, 209, 255));
	m_text.setOrigin(static_cast<int>(m_text.getGlobalBounds().width / 2), static_cast<int>(m_text.getGlobalBounds().height / 2));
	m_text.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2 - 50);

	// Create button elements and push_back into vector
	float centerX = APP_WIDTH / 2;
	float centerY = APP_HEIGHT / 2;
	m_button.setTexture(m_buttonTex);
	m_button.setPosition(APP_WIDTH / 2 - m_button.getLocalBounds().width / 2, APP_HEIGHT / 2 + 25 - m_button.getLocalBounds().height / 2);

	m_continue.setCharacterSize(16);
	m_continue.setColor(sf::Color(89, 106, 209, 255));
	m_continue.setPosition(static_cast<int>((m_button.getPosition().x + m_button.getLocalBounds().width / 2 - m_continue.getGlobalBounds().width / 2)),
		                   static_cast<int>((m_button.getPosition().y + m_button.getLocalBounds().height / 2 - m_continue.getGlobalBounds().height / 2) - 5));

	m_cursorTex.loadFromFile("Assets/Textures/cursor.png");
	m_cursor.setTexture(m_cursorTex);
	m_cursor.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2);

	std::cout << "GameOverState Init" << std::endl;
}

void GameOverState::pause()
{
	std::cout << "GameOverState Pause" << std::endl;
}

void GameOverState::resume()
{
	std::cout << "GameOverState Resume" << std::endl;
}

void GameOverState::update(const sf::Time& dt)
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_stateManager.quit();
			break;

		case sf::Event::MouseButtonPressed:

			m_mousePosition = sf::Mouse::getPosition(m_window);

			// Continue button is clicked...
			if (m_mousePosition.x > m_button.getPosition().x &&
				m_mousePosition.y > m_button.getPosition().y &&
				m_mousePosition.x < m_button.getPosition().x + m_button.getGlobalBounds().width &&
				m_mousePosition.y < m_button.getPosition().y + m_button.getGlobalBounds().height )
			{
				m_next = StateManager::build<IntroState>(m_stateManager, m_window, true);
			}
			break;

		default:
			break;
		}
	}

	int mouseX = sf::Mouse::getPosition(m_window).x;
	int mouseY = sf::Mouse::getPosition(m_window).y;

	if (mouseX > 0 && mouseX < APP_WIDTH - 9 &&
		mouseY > 0 && mouseY < APP_HEIGHT - 16)
	{
		m_cursor.setPosition(mouseX - 9, mouseY - 7);
	}
}

void GameOverState::draw()
{
	m_window.clear();
	m_window.draw(m_bg);
	m_window.draw(m_button);
	m_window.draw(m_congrats);
	m_window.draw(m_text);
	m_window.draw(m_continue);
	m_window.draw(m_cursor);
	m_window.display();
}