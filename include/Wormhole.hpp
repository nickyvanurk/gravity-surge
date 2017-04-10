#ifndef WORMHOLE_HPP
#define WORMHOLE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Wormhole
{
public:
	Wormhole(const float& xCoord = 0, const float& yCoord = 0);
	void		draw(sf::RenderWindow& window);

	void setPosition(const float& xCoord, const float& yCoord);
	sf::Vector2f getPositition();

private:
	float x, y;
	sf::Texture texture;
	sf::Sprite	sprite;
};
#endif