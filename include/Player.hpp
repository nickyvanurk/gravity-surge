#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
	class RenderWindow;
	class Time;
}

class Player
{
public:
	Player(const float& x = 0, const float& y = 0, const bool& gravityEnable = false);
	void		update(const sf::Time& dt);
	void		draw(sf::RenderWindow& window);

	void		setReset(const float& xCoord, const float& yCoord);
	void		reset();

	void         setPosition(const float& x, const float& y);
	sf::Vector2f getPosition();

public:
	float			x, y, vx, vy, r, rotation;
	float			resetX, resetY;
	bool			gravityEnable;
	sf::Vector2f	m_posLastFrame;

private:
	sf::Texture m_texture;
	sf::Sprite	m_sprite;
};

#endif // !PLAYER_HPP