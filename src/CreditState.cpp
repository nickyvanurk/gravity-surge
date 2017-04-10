#include "CreditState.hpp"
#include "StateManager.hpp"
#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

CreditState::CreditState(StateManager& stateManager, sf::RenderWindow& window, bool replace)
	: State{ stateManager, window, replace }
	, m_mousePosition{ 0, 0 }
{
	m_bgTex.loadFromFile("Assets/Textures/bg.png");
	m_bg.setTexture(m_bgTex, true);

	// Tile the background
	m_bgTex.setRepeated(true);
	m_bg.setTextureRect(sf::IntRect{ 0, 0, APP_WIDTH, APP_HEIGHT });

	m_buttonTex.loadFromFile("Assets/Textures/Menu/button.png");
	m_button.setTexture(m_buttonTex, true);
	m_button.setPosition(APP_WIDTH / 2 - 200 - m_button.getGlobalBounds().width / 2,
		                 APP_HEIGHT / 2 + 200 - m_button.getGlobalBounds().height / 2);

	m_font.loadFromFile("Assets/Fonts/HelveticaLTStd-Roman.otf");
	m_text.setFont(m_font);
	m_text.setString("-------------------------------- Gravity Surge -------------------------------\n\nA game programmed in a week to serve as a school project.\nProgrammed in C++ and SFML. Made by Nicky van Urk.\n\nThursday October 9th, 2014.");
	m_text.setCharacterSize(16);
	m_text.setColor(sf::Color(89, 106, 209, 255));
	m_text.setPosition(APP_WIDTH / 2 - 240, APP_HEIGHT / 2 - 200);

	m_cursorTex.loadFromFile("Assets/Textures/cursor.png");
	m_cursor.setTexture(m_cursorTex);
	m_cursor.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2);

	std::cout << "CreditState Init" << std::endl;
}

void CreditState::pause()
{
	std::cout << "CreditState Pause" << std::endl;
}

void CreditState::resume()
{
	std::cout << "CreditState Resume" << std::endl;
}

void CreditState::update(const sf::Time& dt)
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
			case sf::Keyboard::Escape:
				m_next = StateManager::build<MenuState>(m_stateManager, m_window, true);
				break;

			default:
				break;
			}
			break;

		case sf::Event::MouseButtonPressed:
			m_mousePosition = sf::Mouse::getPosition(m_window);

			if (m_mousePosition.x > m_button.getPosition().x &&
				m_mousePosition.y > m_button.getPosition().y &&
				m_mousePosition.x < m_button.getPosition().x + m_button.getLocalBounds().width &&
				m_mousePosition.y < m_button.getPosition().y + m_button.getLocalBounds().height)
			{
				m_next = StateManager::build<MenuState>(m_stateManager, m_window, true);
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

void CreditState::draw()
{
	m_window.clear();
	m_window.draw(m_bg);
	m_window.draw(m_text);
	m_window.draw(m_button);
	m_window.draw(m_cursor);
	m_window.display();
}