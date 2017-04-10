#ifndef PLANET_HPP
#define PLANET_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
	class RenderWindow;
	class Time;
}

class Planet
{
public:
	Planet(const std::string& size, float x, float y, bool moveable, bool ignore, sf::Texture& texture);
	void update(const sf::Time& dt);
	void draw(sf::RenderWindow& window);

	void setPosition(float x, float y);
	sf::Vector2f getPosition();

	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity();

	void setRadius(float r);
	float getRadius();

	void setMass(float m);
	float getMass();

	sf::Vector2f getGlobalPosition();

	void setOrigin(float x, float y);
	void setRotate(float angle);

public:
	bool	m_moveable, m_ignore;

private:
	std::string m_size;
	sf::Sprite m_sprite;
	float x, y, vx, vy, r, m, rotate;
};

#endif