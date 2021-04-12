#include "Bar.h"

Bar::Bar() : m_num(0)
{
}

Bar::Bar(int num) : m_num(num)
{
}

Bar::Bar(int width, int num, int dy) : m_width(width), m_num(num), m_dy(dy)
{
	this->rect = new sf::RectangleShape(sf::Vector2f(m_width, m_dy * m_num));
	this->rect->setOrigin(0, m_dy * m_num);
	this->rect->setFillColor(sf::Color(175, 205, 255));
	this->rect->setOutlineThickness(1.0f);
	this->rect->setOutlineColor(sf::Color::Black);
}

Bar::~Bar()
{
	delete this->rect;
}

sf::RectangleShape* Bar::getRect()
{
	return this->rect;
}

int Bar::getNum()
{
	return this->m_num;
}

void Bar::setNum(int num)
{
	this->m_num = num;
	this->rect->setSize(sf::Vector2f(m_width, m_dy * m_num));
	this->rect->setOrigin(0, m_dy * m_num);
}

