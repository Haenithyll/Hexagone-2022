#include "Simulation.hpp"

# define M_PI 3.14159265358979323846

void Simulation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const float diameter = 150.f;
	const float radius = diameter / 2.f;

	const float angle = M_PI / 3.f;
	const float cos = cosf(angle);
	const float sin = sinf(angle);

	const float offsetY = sin * radius;

	const float stepX = radius * 1.5f;
	const float stepY = offsetY*  2.f;

	sf::Vertex line[7];
	sf::Vector2f center;

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			center = sf::Vector2f(i * stepX, j * stepY);

			if (i % 2 != 0)
				center.y += offsetY;

			line[0] = sf::Vector2f(center.x + radius, center.y);
			line[1] = sf::Vector2f(center.x + cos * radius, center.y - sin * radius);
			line[2] = sf::Vector2f(center.x - cos * radius, center.y - sin * radius);
			line[3] = sf::Vector2f(center.x - radius, center.y);
			line[4] = sf::Vector2f(center.x - cos * radius, center.y + sin * radius);
			line[5] = sf::Vector2f(center.x + cos * radius, center.y + sin * radius);

			line[6] = line[0];

			target.draw(line, 7, sf::LineStrip, states);
		}
	}
}