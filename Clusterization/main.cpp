#include <SFML\Graphics.hpp>
#include <math.h>

const int K = 10;
const int IterationCount = 30;
using Centroids = std::vector<sf::Color>;
using ClosestCentroidIndices = std::vector<int>;
using ClosestCentroidLength = std::vector<int>;

void changeColors(sf::Image& image, ClosestCentroidIndices ids, Centroids centroids);
Centroids initializeCentroids(sf::Image image, int K);
ClosestCentroidIndices findClosestCentroids(const sf::Image& image, Centroids centroids);
Centroids computeMeans(sf::Image& image, ClosestCentroidIndices ids, int k);

struct ColorBuf
{
	int r, g, b;
	int count;
	ColorBuf() : r(0), g(0), b(0), count(0) {}

	ColorBuf& operator += (const sf::Color& c)
	{
		count++;
		r += c.r;
		g += c.g;
		b += c.b;
		return *this;
	}
};

int main()
{
	sf::Texture texture;
	texture.loadFromFile("putin.png");
	auto image = texture.copyToImage();		//Copy the texture pixels to an image

	Centroids centroids = initializeCentroids(image, K);

	ClosestCentroidIndices ids;
	
	for (int it = 0; it < IterationCount; ++it)
	{
		ClosestCentroidIndices ids = findClosestCentroids(image, centroids);
		centroids = computeMeans(image, ids, K);	
  
	}

	changeColors(image, ids, centroids);			

	texture.update(image);
	image.saveToFile("result.png");

	sf::Sprite photo;
	photo.setTexture(texture);

	sf::Vector2u size = photo.getTexture()->getSize();
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "My window");

	while (window.isOpen())
	{
		window.clear(sf::Color::Color(50, 50, 50));

		window.draw(photo);

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

Centroids computeMeans(sf::Image& image, ClosestCentroidIndices ids, int k)
{
	Centroids result;
	result.resize(k);
	std::vector<ColorBuf> colorbuf;
	colorbuf.resize(K);
	for (int i = 0; i < ids.size(); i++)
	{
		colorbuf[ids[i]] += image.getPixel(i % image.getSize().x, i / image.getSize().x);
	}
	for (int i = 0; i < K; i++)
	{
		if (colorbuf[i].count != 0)
		{
			colorbuf[i].r /= colorbuf[i].count;
			colorbuf[i].g /= colorbuf[i].count;
			colorbuf[i].b /= colorbuf[i].count;
		}
	}
	for (int i = 0; i < K; i++)
	{
		result[i] = sf::Color(colorbuf[i].r, colorbuf[i].g, colorbuf[i].b);
	}
	return result;
}

void changeColors(sf::Image& image, ClosestCentroidIndices ids, Centroids centroids)
{
	for (int i = 0; i < ids.size(); i++)
	{
		image.setPixel(i % image.getSize().x, i / image.getSize().y, centroids[ids[i]]);
	}
}

Centroids initializeCentroids(sf::Image image, int K)
{
	Centroids result;
	for (int i = 0; i < K; ++i)
	{
		result.push_back(image.getPixel(rand() % image.getSize().x, rand() % image.getSize().y));
	}
	return result;
}

double getDistance(sf::Color& centroid, sf::Color& pixel)
{
	int dr = centroid.r - pixel.r;
	int dg = centroid.g - pixel.g;
	int db = centroid.b - pixel.b;
	return sqrt(dr * dr + dg * dg + db * db);
}

ClosestCentroidIndices findClosestCentroids(const sf::Image& image, Centroids centroids)
{
	ClosestCentroidIndices result;
	result.resize(image.getSize().x * image.getSize().y);
	ClosestCentroidLength length;
	length.resize(K);
	int minDistance = length[0];
	int numCentroid = 0;
	for (int i = 0; i < image.getSize().y; i++)
	{
		for (int n = 0; n < image.getSize().x; n++)
		{
			for (int m = 0; m < K; m++)
			{
				length[m] = getDistance(centroids[m], image.getPixel(n, i));
			}	

			//for k centroids
			for (int k = 0; k < K; k++)
			{
				if (minDistance > length[k])
				{
					minDistance = length[k];
					numCentroid = k;
				}
			}
			result[i * image.getSize().x + n] = numCentroid;
		}
	}
	return result;
}
