

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

enum directions { IDLE = 0, LEFT, RIGHT, DOWN, UP};

int main()
{

	std::srand(static_cast<unsigned>(time(0)));


	sf::RenderWindow window(sf::VideoMode(1280, 720), "Juego de Aventura", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Resources/images/background.jpg");
	sf::Sprite background;
	background.setTexture(backgroundTexture);

	sf::Texture texture;
	texture.loadFromFile("Resources/images/sprite_sheet.png");

	sf::Sprite sprite;
	sf::IntRect currentFrame(0, 0, 64, 64);

	sprite.setTextureRect(currentFrame);
	sprite.setTexture(texture);

	int currentDirecion = 0;

	std::vector<sf::CircleShape> coins;

	int quantityCoins = 5;

	for (int i = 0; i < 5; i++)
	{
		sf::CircleShape coin;
		coin.setRadius(8.f);
		coin.setFillColor(sf::Color::Yellow);
		coin.setPosition(sf::Vector2f(
			static_cast<float>(std::rand() % window.getSize().x) - static_cast<unsigned>(coin.getRadius()),
			static_cast<float>(std::rand() % window.getSize().y) - static_cast<unsigned>(coin.getRadius()))
		);
		coins.push_back(coin);
	}

	int points = 0;

	sf::Font font;
	font.loadFromFile("Fonts/Poppins-Bold.otf");
	sf::Text pointsText;
	pointsText.setFont(font);
	pointsText.setCharacterSize(20);
	pointsText.setFillColor(sf::Color::Red);
	pointsText.setPosition(sf::Vector2f(10.f, 10.f));

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			sprite.move(-7.f, 0.f);
			currentDirecion = LEFT;
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			sprite.move(7.f, 0.f);
			currentDirecion = RIGHT;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			sprite.move(0.f, -7.f);
			currentDirecion = UP;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sprite.move(0.f, 7.f);
			currentDirecion = DOWN;

		}
			

		if (currentDirecion == LEFT)
		{
			currentFrame.top = 64;
			sprite.setTextureRect(currentFrame);
		} else if (currentDirecion == RIGHT)
		{
			currentFrame.top = 128;
			sprite.setTextureRect(currentFrame);
		}
		else if (currentDirecion == UP)
		{
			currentFrame.top = 192;
			sprite.setTextureRect(currentFrame);
		}
		else if (currentDirecion == DOWN)
		{
			currentFrame.top = 0;
			sprite.setTextureRect(currentFrame);
		}
		else {
			currentDirecion = IDLE;
		}

		for (int i = 0; i < coins.size(); i++)
		{
			if (sprite.getGlobalBounds().intersects(coins[i].getGlobalBounds()))
			{
				coins.erase(coins.begin() + i);
				points++;
			}
		}

		std::stringstream ss;

		ss << "Points: " << points << "\n";

		pointsText.setString(ss.str());

		window.clear(sf::Color(255, 255, 255));

		window.draw(background);
		window.draw(pointsText);
		
		for (size_t i = 0; i < coins.size(); i++) {
			window.draw(coins[i]);
		}
		
		window.draw(sprite);
		

		window.display();

	}
	return 0;
}