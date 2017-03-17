#include <SFML\Graphics.hpp>
#include "vector2.h"
#include <cstdlib>
#include <math.h>

#define HEIGHT 600
#define WIDTH 800


class MaterialPoint
{
public:

	Vector2 GetImpulse() const;

	Vector2 position;
	Vector2 velosity;
	Vector2 acceleration;

	void update(float dt)
	{
		position += velosity * dt;
	}

	float mass;
};

class Ball : public MaterialPoint
{
public:
	float radius;
	int type;
};

Vector2 convert(const sf::Vector2i& v)
{
	return Vector2(v.x, v.y);
}


int main()
{
	//new window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");

  std::vector<Ball> particles;

  //use time
  sf::Clock clock;

  float lastClickTime = 0;

  while (window.isOpen())
  {
	  sf::Time time = clock.getElapsedTime();

	  window.clear(sf::Color::Color(50, 50, 50));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (time.asMilliseconds() - lastClickTime > 100)
		{
			Ball particle;
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			/*
			 ненужные скобки particle.position = (convert(mousePosition));
			*/
			particle.position = (convert(mousePosition));
			particle.velosity = Vector2(-20 + rand() % 40 , -20 + rand() % 40);
			particle.radius = rand() % 4 +3;
			/*
			для 2д ~r^2
			*/
			particle.mass = pow(particle.radius, 3);			//for example mass = radius^3
			particles.push_back(particle);
			lastClickTime = time.asMilliseconds();
		}
		
	}

	//Drawing
	for (auto i = particles.begin(); i != particles.end(); i++)
	{
		sf::CircleShape particle(i->radius);
		particle.setFillColor(sf::Color::White);
		particle.setPosition(i->position.x, i->position.y);
		
		//Bounce off the walls
		
		/*
		возможно что частицы могут "застревать в стенке" при большой скорости удара.
		при обработке удара со стеной также лучше проверять, что скорость такова, что 
		шар летит в стену, а не от нее
		*/
		if (i->position.x < i->radius/2)
		{
			i->velosity.x = -(i->velosity.x);
		}

		if (i->position.x > WIDTH - i->radius/2)
		{
			i->velosity.x = -(i->velosity.x);
		}

		if (i->position.y < i->radius/2)
		{
			i->velosity.y = -(i->velosity.y);
		}

		if (i->position.y > HEIGHT - i->radius/2)
		{
			i->velosity.y = -(i->velosity.y);
		}

		//Collision of particles

			for (auto j = particles.begin(); j != particles.end(); j++)
			{
				Vector2 n = (j->position - i->position).Norm();
				Vector2 d = (j->position - i->position);
				Vector2 dv = (j->velosity - i->velosity);

				if (j != i && d.Len() < (j->radius + i->radius) && dv * d <= 0 )
				{
					//This will generate a number from 0.0 to 1.0
					float bounceFactor =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					
					Vector2 pulse = (n * ((dv / (1 / i->mass + 1 / j->mass)) * n)) * (1 + bounceFactor);
					
					/*
					 вы разве += и -= не переопределили для своего Vector2
					*/
					j->velosity = j->velosity + pulse / j->mass;
					i->velosity = i->velosity - pulse / i->mass;
				}
			}
		/*
		попросите Максима П. или Павла К. вам пояснить как dt лучше находить.
		константа - не лучшее решение
		*/
		i->update(0.01);

		window.draw(particle);
	}
	
    window.display();

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
