#pragma once

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Drawable.hpp"

class Simulation : public sf::Drawable
{
	public:
		void Reset();
		void Update();

		sf::FloatRect GetGlobalBounds();

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
