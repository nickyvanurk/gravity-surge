#include "Howto2State.hpp"
#include "StateManager.hpp"
#include "Howto1State.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

Howto2State::Howto2State(StateManager& stateManager, sf::RenderWindow& window, bool replace)
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
	m_text.setString("While exploring the universe your ship's warp drive broke down.\nWhile floating endlessly in space your crew came up with the\nidea to make use of wormholes to get back to planet Earth.\nBut there is no quick way, no one knows where the wormhole's\nwill lead you.\n\nClick and hold your left mouse button on the spaceship as you\ndrag a line. Release to propel the spaceship into given direction.\nDodge planets and black holes as you explore the galaxy and make way\nto a wormhole, resulting in you being teleported to a different section\nin space!\n\nGood Luck, adventurer!");
	m_text.setCharacterSize(16);
	m_text.setColor(sf::Color(89, 106, 209, 255));
	m_text.setPosition(APP_WIDTH / 2 - 240, APP_HEIGHT / 2 - 200);

	m_cursorTex.loadFromFile("Assets/Textures/cursor.png");
	m_cursor.setTexture(m_cursorTex);
	m_cursor.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2);

	std::cout << "Howto2State Init" << std::endl;
}

void Howto2State::pause()
{
	std::cout << "Howto2State Pause" << std::endl;
}

void Howto2State::resume()
{
	std::cout << "Howto2State Resume" << std::endl;
}

void Howto2State::update(const sf::Time& dt)
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
				m_next = StateManager::build<Howto1State>(m_stateManager, m_window, true);
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
				m_next = StateManager::build<Howto1State>(m_stateManager, m_window, true);
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

void Howto2State::draw()
{
	m_window.clear();
	m_window.draw(m_bg);
	m_window.draw(m_text);
	m_window.draw(m_button);
	m_window.draw(m_cursor);
	m_window.display();
}