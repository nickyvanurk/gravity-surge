#include "SelectState.hpp"
#include "StateManager.hpp"
#include "MenuState.hpp"
#include "PlayState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <string>
#include <fstream>
#include <iostream>

SelectState::SelectState(StateManager& stateManager, sf::RenderWindow& window, bool replace)
	: State{ stateManager, window, replace }
	, m_mousePosition{ 0, 0 }
{
	m_bgTex.loadFromFile("Assets/Textures/bg.png");
	m_bg.setTexture(m_bgTex, true);

	// Tile the background
	m_bgTex.setRepeated(true);
	m_bg.setTextureRect(sf::IntRect{ 0, 0, APP_WIDTH, APP_HEIGHT });

	m_font.loadFromFile("Assets/Fonts/HelveticaLTStd-Roman.otf");

	m_buttonTex.loadFromFile("Assets/Textures/Menu/button.png");
	m_button.setTexture(m_buttonTex, true);
	m_button.setPosition(APP_WIDTH / 2 - 350, APP_HEIGHT / 2 + 230);

	m_cursorTex.loadFromFile("Assets/Textures/cursor.png");
	m_cursor.setTexture(m_cursorTex);
	m_cursor.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2);

	// Generate level select grid
	int count = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{

			m_buttons.push_back(std::move(UIElement(count + 1, m_font, false)));
			m_buttons[count].setPosition(10 + (j * m_buttons[count].getSize().x) + (j * 10),
				10 + (i * m_buttons[count].getSize().y) + (i * 10));
			++count;
		}
	}

	// Read single character from file and save in string 'line'
	std::string line;
	std::ifstream myfile("Assets/Levels/Progress.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		myfile.close();
	}
	else std::cout << "Unable to open 'Progress.txt'";

	// Activate levels up to the number saved in string 'line'
	for (int i = 0; i < std::stoi(line) && i < 30; ++i)
	{
		m_buttons[i].setActive(true);
		// Function that only recolores the elements.
		m_buttons[i].updateActive();
	}

	std::cout << "SelectState Init" << std::endl;
}

void SelectState::pause()
{
	std::cout << "SelectState Pause" << std::endl;
}

void SelectState::resume()
{
	std::cout << "SelectState Resume" << std::endl;
}

void SelectState::update(const sf::Time& dt)
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

			// If clicked, check to see if clicked any button
			for (std::vector<UIElement>::iterator itr = m_buttons.begin(), end = m_buttons.end(); itr != end; ++itr)
			{
				// if button is clicked...
				if ((m_mousePosition.x > itr->getPosition().x && m_mousePosition.y > itr->getPosition().y) &&
					(m_mousePosition.x < itr->getPosition().x + itr->getSize().x && m_mousePosition.y < itr->getPosition().y + itr->getSize().y))
				{
					// and element is set to active...
					if (itr->getActive())
					{
						// update static int inside GameState with current element value
						// and go to the level state
						levelNumber = itr->getValue();
						m_next = StateManager::build<PlayState>(m_stateManager, m_window, true);
					}
				}
			}

			// previous button is clicked...
			if (m_mousePosition.x > m_button.getPosition().x &&
				m_mousePosition.y > m_button.getPosition().y &&
				m_mousePosition.x < m_button.getPosition().x + m_button.getGlobalBounds().width &&
				m_mousePosition.y < m_button.getPosition().y + m_button.getGlobalBounds().height)
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

void SelectState::draw()
{
	m_window.clear();
	m_window.draw(m_bg);
	m_window.draw(m_button);

	for (std::vector<UIElement>::iterator itr = m_buttons.begin(), end = m_buttons.end();
		itr != end; ++itr)
	{
		itr->draw(m_window);
	}

	m_window.draw(m_text);
	m_window.draw(m_cursor);
	m_window.display();
}