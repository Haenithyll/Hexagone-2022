#include "BasicSimulation.hpp"

#include "PseudoRandom.hpp"

#include "Master.hpp"
#include "BenjaminVouallion.hpp"
#include "MerlinPimpain.hpp"
#include "JeanneOskour.hpp"
#include "JosephRepublique.hpp"

#include "Log.hpp"

BasicSimulation::BasicSimulation(int radius, patternCenters(Tilemap::* pattern)()) : Simulation(radius, pattern)
{

}

void BasicSimulation::Reset()
{
	Simulation::Reset();

	mAllCharacters.clear();
	mCharacterPositions.clear();

	sf::Vector3i position = PseudoRandom::GetPosition(Tilemap::Radius());

	Messages BVMessages = Messages({
		new std::string("Tieens comme c'est bizarre"),
		new std::string("Le liban, en grand")
		});

	Messages JOMessages = Messages({
	new std::string("Ils sont dans les campagnes"),
	new std::string("Ils sont dans les villes")
		});

	Messages MPMessages = Messages({
		new std::string("C'est mon projet"),
		new std::string("Nous sommes en simulation")
		});

	Messages JRMessages = Messages({
		new std::string("Ma personne est sacrée"),
		new std::string("Republique, c'est moi")
		});

	int totalMessagesCount = BVMessages.size() + MPMessages.size() + JOMessages.size() + JRMessages.size();

	BenjaminVouallion::Init(totalMessagesCount, BVMessages);
	MerlinPimpain::Init(totalMessagesCount, MPMessages);
	JeanneOskour::Init(totalMessagesCount, JOMessages);
	JosephRepublique::Init(totalMessagesCount, JRMessages);

	std::vector<Party> parties{
		Party::Reprise,
		Party::AgglutinationPatriote,
		Party::EnRoute,
		Party::LesRebelles
	};

	std::vector<Character*> Masters{
		BenjaminVouallion::GetInstance(),
		JeanneOskour::GetInstance(),
		MerlinPimpain::GetInstance(),
		JosephRepublique::GetInstance()
	};

	std::vector<Messages> PartyMessages{
		BVMessages,
		JOMessages,
		MPMessages,
		JRMessages
	};

	for (int partyIndex{ 0 }; partyIndex < parties.size(); ++partyIndex)	// Masters Initialization
	{
		Character* currentMaster = Masters[partyIndex];

		sf::Vector3i position = Tilemap::GetSafeZoneCenter(parties[partyIndex]);
		mCharacterPositions.push_back(position);
		mAllCharacters[std::array<int, 3> { position.x, position.y, position.z }] = currentMaster;
		currentMaster->MoveTo(Tilemap::CoordToPosition(position) * 75.f, 0);
		Tilemap::GetTile(position)->SetCharacter(currentMaster);
	}

	std::vector<std::string> names = AssetManager::GetText("Names");

	for (int partyIndex{ 0 }; partyIndex < parties.size(); ++partyIndex)	// Activists Initialization
		for (int activistIndex{ 0 }; activistIndex < 6; ++activistIndex) {
			if (activistIndex > 5)
				break;

			std::string name = names[PseudoRandom::GetInt(0, names.size() - 1)];

			Character* character = new Activist(name, parties[partyIndex],
				parties[partyIndex % 2 == 0 ? partyIndex + 1 : partyIndex - 1], 50, 2, 5);

			character->SetMessages(PartyMessages[partyIndex]);

			sf::Vector3i position;

			do {
				position = Tilemap::GetSafeZoneCenter(parties[partyIndex]) + (PseudoRandom::GetPosition(1));
			} while (Tilemap::GetTile(position)->GetCharacter() != nullptr);

			mCharacterPositions.push_back(position);
			mAllCharacters[std::array<int, 3> { position.x, position.y, position.z }] = character;
			character->MoveTo(Tilemap::CoordToPosition(position) * 75.f, 0.f);
			Tilemap::GetTile(position)->SetCharacter(character);
		}
}