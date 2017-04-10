#include "Howto1State.hpp"
#include "StateManager.hpp"
#include "MenuState.hpp"
#include "Howto2State.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

Howto1State::Howto1State(StateManager& stateManager, sf::RenderWindow& window, bool replace)
	: State{ stateManager, window, replace }
	, m_mousePosition{ 0, 0 }
{
	m_bgTex.loadFromFile("Assets/Textures/bg.png");
	m_bg.setTexture(m_bgTex, true);

	// Tile the background
	m_bgTex.setRepeated(true);
	m_bg.setTextureRect(sf::IntRect{ 0, 0, APP_WIDTH, APP_HEIGHT });

	m_buttonTex.loadFromFile("Assets/Textures/Menu/button.png");
	m_playerTex.loadFromFile("Assets/Textures/Menu/playerIcon.png");
	m_planetsTex.loadFromFile("Assets/Textures/Menu/planetsIcon.png");
	m_wormholeTex.loadFromFile("Assets/Textures/Menu/wormholeIcon.png");

	// Load font and set it
	m_font.loadFromFile("Assets/Fonts/HelveticaLTStd-Roman.otf");
	m_textPlayer.setFont(m_font);
	m_textPlanets.setFont(m_font);
	m_textWormhole.setFont(m_font);

	m_textPlayer.setString("This is the player. You have control over this object\nwith your left mouse button.");
	m_textPlanets.setString("These are the objects you have to avoid on your journey.\nColliding with these objects will result in a horrible death.");
	m_textWormhole.setString("This is a wormhole, your go-to point to get transported\nto a different section in space.");

	m_textPlayer.setCharacterSize(16);
	m_textPlanets.setCharacterSize(16);
	m_textWormhole.setCharacterSize(16);

	m_textPlayer.setColor(sf::Color(89, 106, 209, 255));
	m_textPlanets.setColor(sf::Color(89, 106, 209, 255));
	m_textWormhole.setColor(sf::Color(89, 106, 209, 255));

	m_textPlayer.setPosition(APP_WIDTH / 2 - 150, APP_HEIGHT / 2 - 200);
	m_textPlanets.setPosition(APP_WIDTH / 2 - 150, APP_HEIGHT / 2 - 40);
	m_textWormhole.setPosition(APP_WIDTH / 2 - 150, APP_HEIGHT / 2 + 100);

	m_playerImg.setTexture(m_playerTex);
	m_planetsImg.setTexture(m_planetsTex);
	m_wormholeImg.setTexture(m_wormholeTex);

	m_playerImg.setPosition(APP_WIDTH / 2 - 240, APP_HEIGHT / 2 - 200);
	m_planetsImg.setPosition(APP_WIDTH / 2 - 240, APP_HEIGHT / 2 - 50);
	m_wormholeImg.setPosition(APP_WIDTH / 2 - 240, APP_HEIGHT / 2 + 100);

	createButton(APP_WIDTH / 2 - 200, APP_HEIGHT / 2 + 200, m_buttonTex, false);
	createButton(APP_WIDTH / 2 + 200, APP_HEIGHT / 2 + 200, m_buttonTex, true);

	m_cursorTex.loadFromFile("Assets/Textures/cursor.png");
	m_cursor.setTexture(m_cursorTex);
	m_cursor.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2);

	std::cout << "Howto1State Init" << std::endl;
}

void Howto1State::pause()
{
	std::cout << "Howto1State Pause" << std::endl;
}

void Howto1State::resume()
{
	std::cout << "Howto1State Resume" << std::endl;
}

void Howto1State::update(const sf::Time& dt)
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

			if (m_mousePosition.x > m_buttons[0]->getPosition().x &&
				m_mousePosition.y > m_buttons[0]->getPosition().y &&
				m_mousePosition.x < m_buttons[0]->getPosition().x + m_buttons[0]->getLocalBounds().width &&
				m_mousePosition.y < m_buttons[0]->getPosition().y + m_buttons[0]->getLocalBounds().height)
			{
				m_next = StateManager::build<MenuState>(m_stateManager, m_window, true);
			}

			if (m_mousePosition.x > m_buttons[1]->getPosition().x - m_buttons[1]->getLocalBounds().width &&
				m_mousePosition.y > m_buttons[1]->getPosition().y &&
				m_mousePosition.x < m_buttons[1]->getPosition().x &&
				m_mousePosition.y < m_buttons[1]->getPosition().y + m_buttons[1]->getLocalBounds().height)
			{
				m_next = StateManager::build<Howto2State>(m_stateManager, m_window, true);
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

void Howto1State::draw()
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
	m_window.draw(m_playerImg);
	m_window.draw(m_planetsImg);
	m_window.draw(m_wormholeImg);
	m_window.draw(m_textPlayer);
	m_window.draw(m_textPlanets);
	m_window.draw(m_textWormhole);
	m_window.draw(m_cursor);
	m_window.display();
}

void Howto1State::createButton(float x, float y, sf::Texture& bg, bool flip)
{
	std::unique_ptr<sf::Sprite> sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite);
	sprite->setTexture(bg);
	sprite->setPosition(x - sprite->getLocalBounds().width / 2, y - sprite->getLocalBounds().height / 2);

	if (flip)
	{
		sprite->setScale(-1.f, 1.f);
		sprite->setPosition(x - sprite->getLocalBounds().width / 2 + sprite->getLocalBounds().width, y - sprite->getLocalBounds().height / 2);
	}

	m_buttons.push_back(std::move(sprite));
}

void Howto1State::freeMemory()
{
	while (!m_buttons.empty())
		m_buttons.pop_back();
}