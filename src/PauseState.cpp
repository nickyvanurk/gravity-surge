#include "PauseState.hpp"
#include "StateManager.hpp"
#include "SelectState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

PauseState::PauseState(StateManager& stateManager, sf::RenderWindow& window, bool replace)
	: State{ stateManager, window, replace }
{
	m_bgTex.loadFromFile("Assets/Textures/bg.png");
	m_bg.setTexture(m_bgTex, true);

	// Tile the background
	m_bgTex.setRepeated(true);
	m_bg.setTextureRect(sf::IntRect{ 0, 0, APP_WIDTH, APP_HEIGHT });

	m_buttonTex.loadFromFile("Assets/Textures/Menu/menuItem.png");

	m_pausedTex.loadFromFile("Assets/Textures/Menu/paused.png");
	m_paused.setTexture(m_pausedTex);
	m_paused.setOrigin(m_paused.getGlobalBounds().width / 2, m_paused.getGlobalBounds().height / 2);
	m_paused.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2 - 100);

	m_font.loadFromFile("Assets/Fonts/HelveticaLTStd-Roman.otf");
	m_continue.setFont(m_font);
	m_exit.setFont(m_font);

	m_cursorTex.loadFromFile("Assets/Textures/cursor.png");
	m_cursor.setTexture(m_cursorTex);
	m_cursor.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2);

	// Set text strings
	m_continue.setString("Resume");
	m_exit.setString("Exit");

	// Create button elements and push_back into vector
	createButton(APP_WIDTH / 2, APP_HEIGHT / 2 - 25, m_buttonTex, m_continue);
	createButton(APP_WIDTH / 2, APP_HEIGHT / 2 + 25, m_buttonTex, m_exit);

	std::cout << "PauseState Init" << std::endl;
}

void PauseState::pause()
{
	std::cout << "PauseState Pause" << std::endl;
}

void PauseState::resume()
{
	std::cout << "PauseState Resume" << std::endl;
}

void PauseState::update(const sf::Time& dt)
{
	sf::Event event;
	int countPosition = 0;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_stateManager.quit();
			break;

		case sf::Event::MouseButtonPressed:
			m_mousePosition = sf::Mouse::getPosition(m_window);

			// if clicked check if button is clicked
			for (std::vector<std::unique_ptr<sf::Sprite>>::iterator
				itr = m_buttons.begin(), end = m_buttons.end(); itr != end; ++itr)
			{
				// button is clicked
				if ((m_mousePosition.x > (*itr)->getPosition().x && m_mousePosition.y > (*itr)->getPosition().y) &&
					(m_mousePosition.x < (*itr)->getPosition().x + (*itr)->getLocalBounds().width &&
					m_mousePosition.y < (*itr)->getPosition().y + (*itr)->getLocalBounds().height))
				{
					freeMemory();

					// check to see what button has been clicked
					switch (countPosition)
					{
					case 0:
						m_stateManager.lastState();
					case 1:
						m_next = StateManager::build<SelectState>(m_stateManager, m_window, true);
						break;

					default:
						break;
					}

					/* no need to check for other buttons anymore
					* so break out of the for loop, if you don't the
					* loop tries to 'scan' the other buttons but they are
					* already deleted by freeMemory()
					*/
					break;
				}
				++countPosition;
			}

			if (countPosition != 0)
				countPosition = 0;
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

void PauseState::draw()
{
	m_window.clear();
	m_window.draw(m_bg);

	for (std::vector<std::unique_ptr<sf::Sprite>>::iterator
		itr = m_buttons.begin(), end = m_buttons.end(); itr != end; ++itr)
	{
		if (*itr != nullptr)
		{
			m_window.draw(**itr);
		}
	}

	m_window.draw(m_paused);
	m_window.draw(m_continue);
	m_window.draw(m_exit);
	m_window.draw(m_cursor);
	m_window.display();
}

void PauseState::createButton(float x, float y, sf::Texture& bg, sf::Text& title)
{
	std::unique_ptr<sf::Sprite> sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite);
	sprite->setTexture(bg);
	sprite->setPosition(x - sprite->getGlobalBounds().width / 2, y - sprite->getGlobalBounds().height / 2);

	title.setCharacterSize(16);
	title.setColor(sf::Color(89, 106, 209, 255));
	title.setPosition(static_cast<int>(sprite->getPosition().x + sprite->getGlobalBounds().width / 2 - title.getGlobalBounds().width / 2),
		static_cast<int>(sprite->getPosition().y + sprite->getGlobalBounds().height / 2 - title.getGlobalBounds().height / 2 - 5));

	m_buttons.push_back(std::move(sprite));
}

void PauseState::freeMemory()
{
	while (!m_buttons.empty())
		m_buttons.pop_back();
}