#include "State.hpp"

int State::levelNumber = 0;

State::State(StateManager& stateManager, sf::RenderWindow& window, bool replace)
	: m_stateManager{ stateManager }
	, m_window{ window }
	, m_replacing{ replace }
{}

std::unique_ptr<State> State::next()
{
	return std::move(m_next);
}

bool State::isReplacing()
{
	return m_replacing;
}