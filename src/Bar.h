#include "Platform/Platform.hpp"

class Bar
{
public:
	Bar();
	Bar(int height);
	Bar(int height, int width, int delta_y);
	~Bar();
	sf::RectangleShape* getRectangleShape();

	int getHeight();
	void setHeight(int height);

private:
	int height;
	int width;
	int delta_y;
	sf::RectangleShape* rectangle;
};