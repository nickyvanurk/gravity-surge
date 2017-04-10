#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <memory>
#include <stack>

class State;

namespace sf
{
	class RenderWindow;
	class Time;
}

class StateManager
{
public:
	StateManager();

	void run(std::unique_ptr<State> state);

	void nextState();
	void lastState();

	void update(const sf::Time& dt);
	void draw();

	bool running() { return m_running; }
	void quit() { m_running = false; }

	template <typename T>
	static std::unique_ptr<T> build(StateManager& stateManager, sf::RenderWindow& window, bool replace = true);

private:
	// The stack of states
	std::stack<std::unique_ptr<State>> m_states;

	bool m_resume;
	bool m_running;
};

template <typename T>
std::unique_ptr<T> StateManager::build(StateManager& stateManager, sf::RenderWindow& window, bool replace)
{
	return std::unique_ptr<T>(new T(stateManager, window, replace));
}

#endif // !STATEMANAGER_HPP