#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "StateManager.hpp"
#include "IntroState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

class Application
{
public:
	Application();

	void run();

private:
	static const sf::Time TimePerFrame;
	StateManager m_stateManager;
	sf::RenderWindow m_window;
};

#endif // !APPLICATION_HPP