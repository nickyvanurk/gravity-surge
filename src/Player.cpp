#include "Player.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Player::Player(const float& xCoord, const float& yCoord, const bool& gravityEnable) :
x(xCoord),
y(yCoord),
vx(0),
vy(0),
rotation(0),
gravityEnable(gravityEnable),
m_posLastFrame(0, 0)
{
	r = 5;

	m_texture.loadFromFile("Assets/Textures/Game/player.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setRotation(rotation);
	m_sprite.setPosition(x, y);
}

void Player::update(const sf::Time& dt)
{
	x += vx * dt.asSeconds();
	y += vy * dt.asSeconds();
	m_sprite.setPosition(x, y);
	m_sprite.setRotation(rotation);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Player::setReset(const float& xCoord, const float& yCoord)
{
	resetX = xCoord;
	resetY = yCoord;
}

void Player::reset()
{
	x = resetX;
	y = resetY;
	vx = 0;
	vy = 0;
	rotation = 0;
}

void Player::setPosition(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
	m_sprite.setPosition(this->x, this->y);
}

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f(x, y);
}