#pragma once

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Character.hpp"
#include "Tilemap.hpp"
#include  "Log.hpp"
#include "Astar.hpp"

#include "Drawable.hpp"
#include "AssetManager.hpp"
#include "Animable.hpp"

class Simulation : public sf::Drawable, public Animable
{
	public:
		Simulation(int radius, patternCenters(Tilemap::* pattern)());

		virtual void Reset();

		void Step(float duration);
		void EndTurn();

		virtual void Update(float deltaTime);

		int GetTurn();

		int GetIndex();
		int GetCount();

		sf::FloatRect GetGlobalBounds();

		bool Over() { return _over; }

	protected:
		int mIndex = 0;
		int mTurn = 0;
		std::map<std::array<int, 3>, Character*> mAllCharacters;
		std::vector<sf::Vector3i> mCharacterPositions;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool _over = false;
};
