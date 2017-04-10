#include "Planet.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
Planet::Planet(const std::string& size, float x, float y, bool movable, bool ignore, sf::Texture& texture)
	: m_moveable(movable)
	, m_ignore(ignore)
	, m_size(size)
	, x(x)
	, y(y)
	, vx(0)
	, vy(0)
	, m(0)
	, rotate(0)
{
	if (size == "small")
	{
		setMass(10000);
		r = 8;
	}
	else if (size == "medium")
	{
		setMass(50000);
		r = 16;
	}
	else if (size == "large")
	{
		setMass(100000);
		r = 27;
	}
	else if (size == "blackhole")
	{
		setMass(200000);
		r = 8;
	}

	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(x, y);
}

void Planet::update(const sf::Time& dt)
{
	x += vx * dt.asSeconds();
	y += vy * dt.asSeconds();
	m_sprite.setPosition(x, y);
	m_sprite.rotate(rotate);
}

void Planet::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Planet::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	m_sprite.setPosition(x, y);
}

sf::Vector2f Planet::getPosition()
{
	return sf::Vector2f(x, y);
}

void Planet::setVelocity(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
}

sf::Vector2f Planet::getVelocity()
{
	return sf::Vector2f(vx, vy);
}

void Planet::setRadius(float r)
{
	this->r = r;
}

float Planet::getRadius()
{
	return r;
}

void Planet::setMass(float m)
{
	this->m = m;
}

float Planet::getMass()
{
	return m;
}

sf::Vector2f Planet::getGlobalPosition()
{
	return sf::Vector2f(m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width / 2,
		m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height / 2);
}

void Planet::setOrigin(float x, float y)
{
	m_sprite.setOrigin(x, y);
}

void Planet::setRotate(float angle)
{
	rotate = angle;
}