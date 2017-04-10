#include "Application.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / APP_FPS);

Application::Application()
{}

void Application::run()
{
	// Create render window
	m_window.create(sf::VideoMode{ APP_WIDTH, APP_HEIGHT }, APP_TITLE, sf::Style::Titlebar | sf::Style::Close);
	
	// Sync refresh rate with monitor
	m_window.setVerticalSyncEnabled(true);

	// Disable continuous input when holding down a key
	m_window.setKeyRepeatEnabled(false);

	m_window.setMouseCursorVisible(false);

	// Initialize the engine
	m_stateManager.run(StateManager::build<IntroState>(m_stateManager, m_window, true));
	
	// Main loop
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_stateManager.running())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		m_stateManager.nextState();

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			m_stateManager.update(TimePerFrame);
		}
		m_stateManager.draw();
	}

	// Leaving the scope of the 'game' will cleanup the engine
}