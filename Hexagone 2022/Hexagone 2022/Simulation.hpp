#pragma once

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Character.hpp"
#include "Tilemap.hpp"

#include "Drawable.hpp"

class Simulation : public sf::Drawable
{
	public:
		Simulation();

		virtual void Reset();

		void Update();
		void EndTurn();

		int GetTurn();

		int GetIndex();
		int GetCount();

		sf::FloatRect GetGlobalBounds();

	protected:
		int mIndex = 0;
		int mTurn = 0;

		std::vector<Character*> mCharacters;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
