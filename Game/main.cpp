#include <SFML\Graphics.hpp>
#include <iostream>
#define HEIGHT 600
#define WIDTH 800 



void movingCircle(sf::Sprite& circle, sf::RenderWindow& window);
bool maymoving(const sf::Sprite& circle, int direction);

const float Pi = 3.14159f;

struct Bullet 
{
	sf::Vector2f pos;
	sf::Vector2f v;
	sf::Time time;
	void update(float dt)
	{
		pos += v * dt;
	}
};


int main()
{
	//new window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");


	//hero picture
	sf::Texture texture;
	texture.loadFromFile("hero.png");
	sf::Sprite circle(texture);
	circle.setPosition(300, 300);

	//create lazer
	sf::RectangleShape line(sf::Vector2f(900, 5));
	line.setFillColor(sf::Color::Red);

	//create bullets
	std::vector<Bullet> bullets;

	

	//use time
	sf::Clock clock;

	float last_shoot_time = 0;

	while (window.isOpen())
	{
		sf::Time time = clock.getElapsedTime();

		window.clear(sf::Color::Color(50, 50, 50));

		window.draw(circle);
		
		
		//Lazer
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::Vector2f center = circle.getPosition();
			sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;
			line.setPosition(center.x, center.y);
			line.setRotation(atan2f(d.y, d.x) * 180 / Pi);
			window.draw(line);
		}

		//Bullets
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (time.asMilliseconds() - last_shoot_time > 100)
			{
				Bullet bul;
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				bul.pos = circle.getPosition();
				bul.v = sf::Vector2f(mousePosition.x, mousePosition.y) - bul.pos;
				bullets.push_back(bul);
				last_shoot_time = time.asMilliseconds();
			}
			
		}

		for (auto i = bullets.begin(); i != bullets.end(); i++)
		{
			sf::CircleShape bul(5);
			bul.setFillColor(sf::Color::Yellow);
			bul.setPosition(i->pos.x, i->pos.y);
			i->update(0.05);

			//delete bullet
			if (i->pos.x > WIDTH || i->pos.x < 0 || i->pos.y > HEIGHT || i->pos.y < 0)
			{
				i = bullets.erase(i);
			}

			window.draw(bul);
		}

		window.display();

		movingCircle(circle, window);

		//close the window
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}

void movingCircle(sf::Sprite& circle, sf::RenderWindow& window)
{
	//Mouse orientation
	sf::Vector2u circleSize = circle.getTexture()->getSize();
	circle.setOrigin(circleSize.x / 2, circleSize.y / 2);

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f center = circle.getPosition();
	sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;

	circle.setRotation(90 + atan2f(d.y, d.x) * 180 / Pi);

	//move 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && maymoving(circle, 1))
	{
		circle.move(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && maymoving(circle, 2))
	{
		circle.move(1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && maymoving(circle, 3))
	{
		circle.move(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && maymoving(circle, 4))
	{
		circle.move(0, 1);
	}
}

bool maymoving(const sf::Sprite& circle, int direction)
{
	sf::Vector2f center = circle.getPosition();
	sf::Vector2u circleSize = circle.getTexture()->getSize();
	float size = (float)sqrt(circleSize.x * circleSize.x + circleSize.y * circleSize.y) / 2;

	switch (direction)
	{
	case 1:
		return center.x > size;
	case 2:
		return center.x < WIDTH - size;
	case 3:
		return center.y > size;
	case 4:
		return center.y < HEIGHT - size;
	default:
		return false;
	}
}