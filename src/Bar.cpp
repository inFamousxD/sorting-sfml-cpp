#include "Bar.h"

Bar::Bar()
{
	this->height = 0;
}

Bar::Bar(int height)
{
	this->height = height;
}

Bar::Bar(int height, int width, int delta_y)
{
	this->height = height;
	this->width = width;
	this->delta_y = delta_y;

	this->rectangle = new sf::RectangleShape(sf::Vector2f(width, height * delta_y));
	this->rectangle->setOrigin(0, delta_y * height);
	this->rectangle->setFillColor(sf::Color(25, 255, 255));
	this->rectangle->setOutlineThickness(1.0f);
	this->rectangle->setOutlineColor(sf::Color::Black);
}

void Bar::setHeight(int height)
{
	this->height = height;
	this->rectangle->setSize(sf::Vector2f(width, height * delta_y));
	this->rectangle->setOrigin(0, delta_y * height);
}

int Bar::getHeight()
{
	return this->height;
}

Bar::~Bar()
{
	delete this->rectangle;
}

sf::RectangleShape* Bar::getRectangleShape()
{
	return this->rectangle;
}

void Bar::hightlight(bool trigger)
{
	if (trigger)
		this->rectangle->setFillColor(sf::Color(255, 255, 25));
	else
		this->rectangle->setFillColor(sf::Color(25, 255, 255));
}