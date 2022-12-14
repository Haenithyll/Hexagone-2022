#include "Simulation.hpp"
#include "PseudoRandom.hpp"
#include "Tilemap.hpp"
#include "Log.hpp"
#include "JosephRepublique.hpp"
#include "JeanneOskour.hpp"
#include "BenjaminVouallion.hpp"
#include "MerlinPimpain.hpp"
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
	_over = false;
	Tilemap::ResetMap();
}

void Simulation::Step(float duration)
{
	std::random_device rd;
	std::shuffle(mCharacterPositions.begin(), mCharacterPositions.end(), rd);

	sf::Vector3i currentCharacterPosition = mCharacterPositions[mIndex];
	Character* currentCharacter = mAllCharacters[std::array<int, 3>{
		currentCharacterPosition.x,
			currentCharacterPosition.y,
			currentCharacterPosition.z
	}];

	if (!currentCharacter->IsMaster())
	{
		int moveRange = currentCharacter->DecideMoveRange();

		Action action = currentCharacter->DecideAction();

		Log::Print(currentCharacter->GetName(), currentCharacter->GetParty());

		std::vector<sf::Vector3i> pathToTravel;

		if (action == Action::BackToHome)
		{
			sf::Vector3i home = Tilemap::GetSafeZoneCenter(currentCharacter->GetParty());

			pathToTravel = Astar::FindPath(currentCharacterPosition, home, currentCharacter->GetParty());

			if (pathToTravel.size() > 0)
				pathToTravel.erase(pathToTravel.begin());

			currentCharacter->SetLastDirection(home);

			Log::Print("Je retourne ? la safe zone : " + std::to_string(pathToTravel.size()) + " pas");
		}
		else if (action == Action::RandomMove)
		{
			sf::Vector3i last = currentCharacterPosition;

			for (int i = 0; i < moveRange; ++i)
			{
				sf::Vector3i move = PseudoRandom::GetDirection();

				while (Tilemap::GetTile(last + move) == nullptr || move == -currentCharacter->GetLastDirection())
				{
					move = PseudoRandom::GetDirection();
				}

				last = last + move;
				pathToTravel.push_back(last);
				currentCharacter->SetLastDirection(move);
			}

			Log::Print("Je bouge aleatoirement : " + std::to_string(pathToTravel.size()) + " pas");
		}

		for (int i = 0; i < pathToTravel.size(); ++i)
		{
			sf::Vector3i nextPosition = pathToTravel[i];

			if (currentCharacter->LoseEnergy())//If currentCharacter has no energy
			{
				mAllCharacters.erase(std::array<int, 3>{
					currentCharacterPosition.x,
						currentCharacterPosition.y,
						currentCharacterPosition.z
				});

				mCharacterPositions.erase(mCharacterPositions.begin() + mIndex);
				mIndex = (mIndex - 1) % mCharacterPositions.size();

				Tilemap::GetTile(currentCharacterPosition)->SetObstacle(true);

				Log::Print("Je me meurs et me transforme en pierre");

				break;
			}

			Tile* nextTile = Tilemap::GetTile(nextPosition);

			if (nextTile->Obstacle() || (nextTile->GetParty() != currentCharacter->GetParty() && nextTile->GetParty() != None))
			{
				for (int j = i + 1; j < pathToTravel.size(); ++j)
					currentCharacter->LoseEnergy();

				Log::Print("Je me suis cogne donc j'annule mes " + std::to_string(pathToTravel.size() - (i + 1)) + " prochains pas");

				break;
			}

			std::map<std::array<int, 3>, Character*>::iterator nextCharacterIt = mAllCharacters.find(std::array<int, 3> {
				nextPosition.x,
					nextPosition.y,
					nextPosition.z
			});

			if (nextCharacterIt != mAllCharacters.end())
			{
				currentCharacter->Meet(nextCharacterIt->second);

				for (int j = i + 1; j < pathToTravel.size(); ++j)
					currentCharacter->LoseEnergy();

				Log::Print("J'ai fait une rencontre donc j'annule mes " + std::to_string(pathToTravel.size() - (i + 1)) + " prochains pas");

				break;
			}
			else
			{
				//we didn't encounter an obstacle so lastDirection is reset
				currentCharacter->SetLastDirection(sf::Vector3i(0, 0, 0));

				mAllCharacters.erase(std::array{ currentCharacterPosition.x, currentCharacterPosition.y, currentCharacterPosition.z });

				mAllCharacters[std::array{ nextPosition.x, nextPosition.y, nextPosition.z }] = currentCharacter;
				mCharacterPositions[mIndex] = nextPosition;

				Tilemap::GetTile(currentCharacterPosition)->SetCharacter(nullptr);
				Tilemap::GetTile(nextPosition)->SetCharacter(currentCharacter);

				currentCharacter->MoveTo(Tilemap::CoordToPosition(nextPosition) * 75.f, duration / moveRange);
				currentCharacterPosition = nextPosition;

				if (nextTile->GetParty() == currentCharacter->GetParty())
				{
					currentCharacter->MeetMaster();
				}
			}
		}
	}

	mIndex = (mIndex + 1) % mCharacterPositions.size();

	if (mIndex == 0)
		++mTurn;

	int totalMessagesCount = JosephRepublique::GetInstance()->GetTotalMessagesCount();
	if (JosephRepublique::GetInstance()->GetMessages().size() == totalMessagesCount)
	{
		Log::BreakLine();
		Log::Print("Le parti LesRebelles gagne la partie !");
		_over = true;
	}
	else if (JeanneOskour::GetInstance()->GetMessages().size() == totalMessagesCount)
	{
		Log::BreakLine();
		Log::Print("Le parti AgglutinationPatriote gagne la partie !");
		_over = true;
	}
	else if (BenjaminVouallion::GetInstance()->GetMessages().size() == totalMessagesCount)
	{
		Log::BreakLine();
		Log::Print("Le parti Reprise gagne la partie !");
		_over = true;
	}
	else if (MerlinPimpain::GetInstance()->GetMessages().size() == totalMessagesCount)
	{
		Log::BreakLine();
		Log::Print("Le parti EnRoute gagne la partie !");
		_over = true;
	}

	if (!currentCharacter->IsMaster())
		Log::BreakLine();
}

void Simulation::EndTurn()
{
	do
	{
		Step(0.f);
	} while (mIndex > 0 && !_over);
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

	sf::Text x("", AssetManager::GetFont("Default"), 12u);
	x.setFillColor(sf::Color::White);
	x.setOutlineThickness(0.5f);
	x.setOutlineColor(sf::Color::Black);

	sf::Text y("", AssetManager::GetFont("Default"), 12u);
	y.setFillColor(sf::Color::White);
	y.setOutlineThickness(0.5f);
	y.setOutlineColor(sf::Color::Black);

	sf::Text z("", AssetManager::GetFont("Default"), 12u);
	z.setFillColor(sf::Color::White);
	z.setOutlineThickness(0.5f);
	z.setOutlineColor(sf::Color::Black);

	for (const auto& [_, tile] : Tilemap::Tiles())
	{
		auto a = Tilemap::Tiles();

		center = tile->Position();

		center *= radius;

		line[0] = sf::Vector2f(center.x + radius, center.y);
		line[1] = sf::Vector2f(center.x + cos * radius, center.y - sin * radius);
		line[2] = sf::Vector2f(center.x - cos * radius, center.y - sin * radius);
		line[3] = sf::Vector2f(center.x - radius, center.y);
		line[4] = sf::Vector2f(center.x - cos * radius, center.y + sin * radius);
		line[5] = sf::Vector2f(center.x + cos * radius, center.y + sin * radius);

		x.setString(std::to_string(tile->Coordinates().x));
		x.setOrigin(x.getGlobalBounds().width / 2.f, x.getGlobalBounds().height / 2.f);
		x.setPosition(center.x - cos * radius, center.y - sin * radius / 2.5f);

		y.setString(std::to_string(tile->Coordinates().y));
		y.setOrigin(y.getGlobalBounds().width / 2.f, y.getGlobalBounds().height / 2.f);
		y.setPosition(center.x + cos * radius, center.y - sin * radius / 2.5f);

		z.setString(std::to_string(tile->Coordinates().z));
		z.setOrigin(z.getGlobalBounds().width / 2.f, z.getGlobalBounds().height / 2.f);
		z.setPosition(center.x, center.y + radius / 2.f);

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

			case AgglutinationPatriote:
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