#include "Wormhole.hpp"

Wormhole::Wormhole(const float& xCoord, const float& yCoord) :
x(xCoord),
y(yCoord)
{
	texture.loadFromFile("Assets/Textures/Game/wormhole.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(x, y);
}

void Wormhole::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void  Wormhole::setPosition(const float& xCoord, const float& yCoord)
{
	x = xCoord;
	y = yCoord;
	sprite.setPosition(x, y);
}

sf::Vector2f  Wormhole::getPositition()
{
	return sf::Vector2f(x, y);
}