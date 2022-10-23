#include "Simulation.hpp"

#include "Tilemap.hpp"

# define M_PI 3.14159265358979323846

Simulation::Simulation(int radius)
{
	Tilemap::Init(radius);

	Reset();
}

void Simulation::Reset()
{
	mTurn = 0;
	mIndex = 0;
}

void Simulation::Update()
{
	mCharacters[mIndex]->Move();

	mIndex = (mIndex + 1) % mCharacters.size();

	if (mIndex == 0)
		++mTurn;
}

void Simulation::EndTurn()
{
	do
	{
		Update();
	} while (mIndex > 0);
}

int Simulation::GetTurn()
{
	return mTurn;
}

int Simulation::GetIndex()
{
	return mIndex;
}

int Simulation::GetCount()
{
	return mCharacters.size();
}

sf::FloatRect Simulation::GetGlobalBounds()
{
	const float diameter = 150.f;

	return sf::FloatRect(0.f, 0.f, diameter * (Tilemap::Radius() + 0.5f) * 2.f, diameter * (Tilemap::Radius() + 0.5f) * 2.f);
}

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

	for (const auto& tile : Tilemap::Tiles())
	{
		center = tile.second->Position();

		center *= radius;

		line[0] = sf::Vector2f(center.x + radius, center.y);
		line[1] = sf::Vector2f(center.x + cos * radius, center.y - sin * radius);
		line[2] = sf::Vector2f(center.x - cos * radius, center.y - sin * radius);
		line[3] = sf::Vector2f(center.x - radius, center.y);
		line[4] = sf::Vector2f(center.x - cos * radius, center.y + sin * radius);
		line[5] = sf::Vector2f(center.x + cos * radius, center.y + sin * radius);

		line[6] = line[0];

		for (auto& vertex : line)
			vertex.color = sf::Color(245, 245, 220);

		target.draw(line, 7, sf::TrianglesFan, states);

		for (auto& vertex : line)
			vertex.color = sf::Color::Black;

		target.draw(line, 7, sf::LinesStrip, states);
	}
}