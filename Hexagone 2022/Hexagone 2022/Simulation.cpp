#include "Simulation.hpp"

#include "Tilemap.hpp"

#include <random>
#include <algorithm>

# define M_PI 3.14159265358979323846

Simulation::Simulation(int radius, patternCenters(Tilemap::*pattern)())
{
	Tilemap::Init(radius, pattern);

	Reset();
}

void Simulation::Reset()
{
	mTurn = 0;
	mIndex = 0;
}

void Simulation::Step()
{
	sf::Vector3i currentCharacterPosition = mCharacterPositions[mIndex];
	Character* currentCharacter = mAllCharacters[std::array<int, 3>{
		currentCharacterPosition.x,
		currentCharacterPosition.y,
		currentCharacterPosition.z
	}];
	int moveRange = currentCharacter->DecideMoveRange();
	Action action = currentCharacter->DecideAction();
	std::vector<sf::Vector3i> pathToTravel;
	if (action == Action::BackToHome)
	{
		//pathToTravel = Tilemap::GetSafeZonePath(_position, currentCharacter->GetParty());
	}
	else if (action == Action::RandomMove)
	{
		for (int i = 0; i < moveRange; ++i)
		{
			sf::Vector3i move = sf::Vector3i(1, 1, 1); // PseudoRandom::GetDirection();
			while (Tilemap::GetTile(currentCharacterPosition + move) == nullptr || move == currentCharacter->GetLastDirection())
			{
				move = sf::Vector3i(1, 0, 1); // PseudoRandom::GetDirection();
			}

			pathToTravel.push_back(currentCharacterPosition + move);
			currentCharacter->SetLastDirection(move);
		}
	}

	for (sf::Vector3i nextPosition : pathToTravel)
	{
		if (currentCharacter->LoseEnergy())//if Character has no energy
		{
			//_isDead = true;
			mAllCharacters.erase(std::array<int, 3>{
				currentCharacterPosition.x,
					currentCharacterPosition.y,
					currentCharacterPosition.z}
			);
			mIndex = (mIndex - 1) % mCharacterPositions.size();
			Tilemap::GetTile(currentCharacterPosition)->SetObstacle();
		}
		Tile* nextTile = Tilemap::GetTile(nextPosition);
		if (nextTile->Obstacle() || nextTile->GetParty() != currentCharacter->GetParty())
			break;

		//we didn't encounter an obstacle so lastDirection is reset
		currentCharacter->SetLastDirection(sf::Vector3i(0, 0, 0));

		std::map<std::array<int, 3>, Character*>::iterator nextCharacterIt = mAllCharacters.find(std::array<int, 3> {
			nextPosition.x,
				nextPosition.y,
				nextPosition.z
		});
		if (nextCharacterIt != mAllCharacters.end())
		{
			currentCharacter->Meet(nextCharacterIt->second);
		}
		else
		{
			if (nextTile->GetParty() == currentCharacter->GetParty())
			{
				currentCharacter->MeetMaster();
			}
		}
	}
	mIndex = (mIndex + 1) % mCharacterPositions.size();

	if (mIndex == 0)
		++mTurn;
}

void Simulation::EndTurn()
{
	std::random_device rd;
	std::shuffle(mCharacterPositions.begin(), mCharacterPositions.end(), rd);
	do
	{
		Step();
	} while (mIndex > 0);
}

void Simulation::Update(float deltaTime)
{
	for (const auto& [position, character] : mAllCharacters)
		character->Update(deltaTime);
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
	return mAllCharacters.size();
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

	sf::Vertex line[7];
	sf::Vector2f center;

	for (const auto& [_, tile] : Tilemap::Tiles())
	{
		center = tile->Position();

		center *= radius;

		line[0] = sf::Vector2f(center.x + radius, center.y);
		line[1] = sf::Vector2f(center.x + cos * radius, center.y - sin * radius);
		line[2] = sf::Vector2f(center.x - cos * radius, center.y - sin * radius);
		line[3] = sf::Vector2f(center.x - radius, center.y);
		line[4] = sf::Vector2f(center.x - cos * radius, center.y + sin * radius);
		line[5] = sf::Vector2f(center.x + cos * radius, center.y + sin * radius);

		line[6] = line[0];

		for (auto& vertex : line)
		{
			switch (tile->GetParty())
			{
			case LesRebelles:
				vertex.color = sf::Color::Red;

				break;

			case Reprise:
				vertex.color = sf::Color::Blue;

				break;

			case P3:
				vertex.color = sf::Color::Cyan;

				break;

			case EnRoute:
				vertex.color = sf::Color::Yellow;

				break;

			default:
				vertex.color = sf::Color(245, 245, 220);

				break;
			}

			if (tile->Obstacle())
				vertex.color = sf::Color(75, 75, 75);
		}

		target.draw(line, 7, sf::TrianglesFan, states);

		for (auto& vertex : line)
			vertex.color = sf::Color::Black;

		target.draw(line, 7, sf::LinesStrip, states);

		if (tile->Obstacle())
		{
			sf::Sprite obstacle(AssetManager::GetTexture("Obstacle"), sf::IntRect(0, 0, 150, 150));

			obstacle.setOrigin(75.f, 75.f);
			obstacle.setPosition(center);

			target.draw(obstacle);
		}
	}

	for (const auto& [position, character] : mAllCharacters)
		target.draw(*character);
}