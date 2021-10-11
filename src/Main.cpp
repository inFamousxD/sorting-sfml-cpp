#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(200.0f * screenScalingFactor, 200.0f * screenScalingFactor), "SFML works!");
	platform.setIcon(window.getSystemHandle());

	// sf::CircleShape shape(window.getSize().x / 2);
	// shape.setFillColor(sf::Color::White);

	// sf::Texture shapeTexture;
	// shapeTexture.loadFromFile("content/sfml.png");
	// shape.setTexture(&shapeTexture);

	std::vector<sf::RectangleShape> rectangles;

	for (int i = 0; i < 10; ++i)
	{
		sf::RectangleShape shape(sf::Vector2f(1, window.getSize().y - i * 25));
		shape.setPosition(i * 10, 0);
		rectangles.insert(rectangles.begin(), shape);
	}
	// sf::RectangleShape shape(sf::Vector2f(2, window.getSize().x));

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		// window.draw(shape);
		for (const auto& shape : rectangles)
			window.draw(shape);
		window.display();
	}

	return 0;
}
