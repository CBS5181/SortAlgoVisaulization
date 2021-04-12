#pragma once
#include <SFML/Graphics.hpp>

class Bar {
public:
	Bar();
	Bar(int num);
	Bar(int width, int num, int dy);
	~Bar();
	sf::RectangleShape* getRect();
	int getNum();
	void setNum(int num);

private:
	int m_width, m_num, m_dy;
	sf::RectangleShape* rect;
};