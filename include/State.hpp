#ifndef STATE_HPP
#define STATE_HPP

#include "Constants.hpp"

#include <memory>

class StateManager;

namespace sf
{
	class RenderWindow;
	class Time;
}

class State
{
public:
	State(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);
	virtual ~State() = default;

	State(const State&) = delete;
	State& operator= (const State&) = delete;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void update(const sf::Time& dt) = 0;
	virtual void draw() = 0;

	std::unique_ptr<State> next();

	bool isReplacing();

	static int levelNumber;

protected:
	StateManager& m_stateManager;
	sf::RenderWindow& m_window;

	bool m_replacing;

	std::unique_ptr<State> m_next;
};

#endif // !STATE_HPP