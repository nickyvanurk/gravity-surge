#include "PlayState.hpp"
#include "StateManager.hpp"
#include "PauseState.hpp"
#include "SelectState.hpp"
#include "GameOverState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

struct Line
{
	float x1;
	float y1;
	float x2;
	float y2;
} line;

std::string& rtrim(std::string& str) {
	size_t endpos = str.find_last_not_of("\r\n");
	if(endpos != std::string::npos) {
		str.substr(0,endpos+1).swap(str);
	}
	return str;
}

PlayState::PlayState(StateManager& stateManager, sf::RenderWindow& window, bool replace)
	: State{ stateManager, window, replace }
	, m_leftMouseDown(false)
	, m_mouseHoverPlayer(false)
	, m_mousePosition{ 0, 0 }
	, m_lineLength{ 0 }
	, m_tries{ 0 }
{
	m_bgTex.loadFromFile("Assets/Textures/bg.png");
	m_moonTex.loadFromFile("Assets/Textures/Game/planetSmall.png");
	m_planetTex.loadFromFile("Assets/Textures/Game/planetMedium.png");
	m_sunTex.loadFromFile("Assets/Textures/Game/planetLarge.png");
	m_blackHoleTex.loadFromFile("Assets/Textures/Game/blackHole.png");

	m_bg.setTexture(m_bgTex, true);

	// Tile the background
	m_bgTex.setRepeated(true);
	m_bg.setTextureRect(sf::IntRect{ 0, 0, APP_WIDTH, APP_HEIGHT });

	m_font.loadFromFile("Assets/Fonts/HelveticaLTStd-Roman.otf");

	std::ostringstream ss;
	ss << "Level: " << levelNumber;

	m_text.setFont(m_font);
	m_text.setCharacterSize(14);
	m_text.setString(ss.str());
	m_text.setColor(sf::Color::White);
	m_text.setPosition(APP_WIDTH / 2 - m_text.getGlobalBounds().width / 2, 10);

	m_triesText.setFont(m_font);
	m_triesText.setCharacterSize(14);
	m_triesText.setString("Tries: " + std::to_string(m_tries));
	m_triesText.setColor(sf::Color::White);
	m_triesText.setPosition(APP_WIDTH - 75, 10);

	// initialize variables.
	float tileSize = 30;
	float screenWidth = APP_WIDTH / tileSize;
	float screenHeight = APP_HEIGHT / tileSize;

	m_cursorTex.loadFromFile("Assets/Textures/cursor.png");
	m_cursor.setTexture(m_cursorTex);
	m_cursor.setPosition(APP_WIDTH / 2, APP_HEIGHT / 2);

	// obtain level data from file.
	bool found;
	std::string data = "";
	std::string line = "";
	std::ifstream myfile("Assets/Levels/level" + std::to_string(levelNumber) + ".txt");
	if (myfile.is_open())
	{
		found = true;
		while (!myfile.eof())
		{
			getline(myfile, line);
			line = rtrim(line);
			data += line;
		}

		myfile.close();
	}
	else
	{
		found = false;
		std::cout << "Level " << levelNumber << " not found in directory." << std::endl;
	}

	// Load planets into vector based on level data.
	if (found)
	{
		int charCount = 0;
		for (int row = 0; row < screenHeight; ++row)
		{
			for (int col = 0; col < screenWidth; ++col)
			{
				switch (data[charCount])
				{
				case 49: // 1
					m_planets.push_back(Planet("small", col * tileSize, row * tileSize, false, false, m_moonTex));
					break;

				case 50: // 2
					m_planets.push_back(Planet("medium", col * tileSize, row * tileSize, false, false, m_planetTex));
					break;

				case 51: // 3
					m_planets.push_back(Planet("large", col * tileSize, row * tileSize, false, false, m_sunTex));
					break;

				case 52: // 4
					m_planets.push_back(Planet("blackhole", col * tileSize, row * tileSize, false, false, m_blackHoleTex));
					break;

				case 53: // 5
					m_planets.push_back(Planet("small", col * tileSize, row * tileSize, false, false, m_moonTex));
					m_planets.back().setOrigin(90, 0);
					m_planets.back().setRotate(1);
					m_planets.push_back(Planet("medium", col * tileSize, row * tileSize, false, false, m_planetTex));
					break;

				case 112: // p
					m_ship.setPosition(col * tileSize, row * tileSize);
					m_ship.setReset(col * tileSize, row * tileSize);
					break;

				case 101: // e
					m_wormhole.setPosition(col * tileSize, row * tileSize);
					break;

				default:
					break;
				}
				++charCount;
			}
		}
	}

	std::cout << "PlayState Init" << std::endl;
}

void PlayState::pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::resume()
{
	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::update(const sf::Time& dt)
{
	processInput();

	for (unsigned int i = 0; i < m_planets.size(); ++i)
	{
		bool collidePlanet = false;
		Planet& p = m_planets[i];
		for (unsigned int j = 0; j < m_planets.size(); ++j)
		{
			if (j == i || p.m_moveable == false)
				continue;

			Planet& p1 = m_planets[j];

			if ((p.m_ignore == true) && (p1.m_ignore == true))
				continue;

			float d = sqrt((p1.getGlobalPosition().x - p.getGlobalPosition().x)*(p1.getGlobalPosition().x - p.getGlobalPosition().x) +
				(p1.getGlobalPosition().y - p.getGlobalPosition().y)*(p1.getGlobalPosition().y - p.getGlobalPosition().y));

			if (d > p.getRadius() + p1.getRadius())
			{
				float vx = p.getVelocity().x;
				float vy = p.getVelocity().y;
				vx += (float)((1.7f * p1.getMass() / (d*d) * (p1.getGlobalPosition().x - p.getGlobalPosition().x) / d) * 70) * dt.asSeconds(); //f = ma => a = f/m
				vy += (float)((1.7f * p1.getMass() / (d*d) * (p1.getGlobalPosition().y - p.getGlobalPosition().y) / d) * 70) * dt.asSeconds();
				p.setVelocity(vx, vy);
			}
			else
			{
				collidePlanet = true;

				// Erase planet on collision with the lesser mass.
				if (m_planets[i].getMass() > m_planets[j].getMass())
					m_planets.erase(m_planets.begin() + j);
				else
					m_planets.erase(m_planets.begin() + i);
			}
		}

		if (!collidePlanet)
			p.update(dt);

		if (m_ship.gravityEnable == false)
			continue;

		float d = sqrt((m_ship.x - p.getGlobalPosition().x)*(m_ship.x - p.getGlobalPosition().x) + (m_ship.y - p.getGlobalPosition().y)*(m_ship.y - p.getGlobalPosition().y));

		if (d > p.getRadius() + m_ship.r)
		{
			m_ship.vx += (float)(p.getMass() / (d*d) * (p.getGlobalPosition().x - m_ship.x) / d); //f = ma => a = f/m
			m_ship.vy += (float)(p.getMass() / (d*d) * (p.getGlobalPosition().y - m_ship.y) / d);
		}
		else
		{
			m_ship.gravityEnable = false;
			m_ship.reset();
			++m_tries;
			m_triesText.setString("Tries: " + std::to_string(m_tries));
		}
	}

	if (m_leftMouseDown)
	{
		m_mousePosition = sf::Mouse::getPosition(m_window);

		line.x1 = m_ship.getPosition().x;
		line.y1 = m_ship.getPosition().y;
		line.x2 = (float)m_cursor.getPosition().x + 9;
		line.y2 = (float)m_cursor.getPosition().y + 7;

		m_lineLength = sqrt((line.x1 - line.x2)*(line.x1 - line.x2) + (line.y1 - line.y2)*(line.y1 - line.y2));

		if ((m_mousePosition.x > m_ship.getPosition().x - 20 && m_mousePosition.x < m_ship.getPosition().x + 20) &&
			(m_mousePosition.y > m_ship.getPosition().y - 20 && m_mousePosition.y < m_ship.getPosition().y + 20))
			m_mouseHoverPlayer = true;

		if (m_mouseHoverPlayer)
		{
			// The Adjacent  between player and mouse.
			float d1 = m_ship.getPosition().y - m_mousePosition.y;
			// The Hypotenuse between player and mouse.
			float d2 = sqrt((m_ship.getPosition().x - m_mousePosition.x)*(m_ship.getPosition().x - m_mousePosition.x) +
				(m_ship.getPosition().y - m_mousePosition.y)*(m_ship.getPosition().y - m_mousePosition.y));
			// Convert the cos from d1 and d2 to radians and then to degrees.
			float result = (float)(acos(d1 / d2)*RAD2DEG);

			// If the mouse on the x-axis is smaller than the player on the x-axis, invert result(degrees).
			if (m_mousePosition.x < m_ship.getPosition().x)
				result = -result;

			// Set the new player rotation.
			m_ship.rotation = result - 90;
		}
	}

	if (!(m_ship.getPosition().x > 0 && m_ship.getPosition().x < APP_WIDTH && m_ship.getPosition().y > 0 && m_ship.getPosition().y < APP_HEIGHT))
	{
		m_ship.gravityEnable = false;
		m_ship.reset();
		++m_tries;
		m_triesText.setString("Tries: " + std::to_string(m_tries));
	}

	m_ship.m_posLastFrame = m_ship.getPosition();

	m_ship.update(dt);

	// Fix ships rotation when moving.
	if (m_ship.gravityEnable)
	{
		float d1 = m_ship.getPosition().x - m_ship.m_posLastFrame.x;
		float d2 = m_ship.getPosition().y - m_ship.m_posLastFrame.y;
		float result = (float)(atan(d2 / d1)*RAD2DEG);

		if (m_ship.vx < 0)
			result += 180;

		m_ship.rotation = result;
	}

	float d = sqrt((m_ship.getPosition().x - m_wormhole.getPositition().x)*(m_ship.getPosition().x - m_wormhole.getPositition().x) +
		(m_ship.getPosition().y - m_wormhole.getPositition().y)*(m_ship.getPosition().y - m_wormhole.getPositition().y));
	if (d < 8)
	{

		// Read single character from file and save in string 'line'
		std::string line;
		std::ifstream myfile("Assets/Levels/Progress.txt");
		if (myfile.is_open())
		{
			getline(myfile, line);
			myfile.close();
		}
		else std::cout << "Unable to open file";

		if (levelNumber != 10)
		{
			if (levelNumber >= std::stoi(line))
			{
				std::ofstream myFile("Assets/Levels/Progress.txt");
				if (myFile.is_open())
				{
					myFile << levelNumber + 1;
					myFile.close();
				}
				else
				{
					//You're in trouble now Mr!
					std::cout << "Could not save level: " << levelNumber;
				}
			}
			m_next = StateManager::build<SelectState>(m_stateManager, m_window, true);
		}
		else
		{
			std::ofstream myFile("Assets/Levels/Progress.txt");
			if (myFile.is_open())
			{
				myFile << 1;
				myFile.close();
			}
			else
			{
				//You're in trouble now Mr!
				std::cout << "Could not reset level" << std::endl;
			}
			m_next = StateManager::build<GameOverState>(m_stateManager, m_window, true);
		}
	}
}

void PlayState::draw()
{
	m_window.clear();
	m_window.draw(m_bg);

	m_ship.draw(m_window);
	m_wormhole.draw(m_window);

	for (std::vector<Planet>::iterator itr = m_planets.begin(), end = m_planets.end();
		itr != end; ++itr)
	{
		itr->draw(m_window);
	}

	if (m_leftMouseDown && m_mouseHoverPlayer)
	{
		sf::Vertex Line[] = {
			sf::Vertex(sf::Vector2f(line.x1, line.y1), sf::Color(217, 236, 250)),
			sf::Vertex(sf::Vector2f(line.x2, line.y2), sf::Color(217, 236, 250))
		};
		m_window.draw(Line, 2, sf::Lines);
	}

	m_window.draw(m_text);
	m_window.draw(m_triesText);
	m_window.draw(m_cursor);
	m_window.display();
}

void PlayState::processInput()
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
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_next = StateManager::build<PauseState>(m_stateManager, m_window, false);
			}
			else if (event.key.code == sf::Keyboard::P)
			{
				m_next = StateManager::build<PauseState>(m_stateManager, m_window, false);
			}
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_leftMouseDown = true;
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_leftMouseDown = false;
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (m_mouseHoverPlayer && m_lineLength >= 8)
				{
					m_ship.gravityEnable = true;

					float xLength = line.x2 - line.x1;
					float yLength = line.y2 - line.y1;
					m_ship.vx = xLength;
					m_ship.vy = yLength;
				}

				m_mouseHoverPlayer = false;
			}
			break;

		default:
			break;
		}
	}

	int mouseX = sf::Mouse::getPosition(m_window).x;
	int mouseY = sf::Mouse::getPosition(m_window).y;

	m_cursor.setPosition(mouseX - 9, mouseY - 7);
}