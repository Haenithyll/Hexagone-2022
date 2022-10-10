#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "Grid.hpp"

namespace gk
{
	enum GameObject
	{
		Free,
		Nil,
		Obstacle,
		White,
		Black
	};

	class Gomoku : public sf::Drawable
	{
		public:
			Gomoku(unsigned startSize = 19u, unsigned gap = 6u);

			sf::Vector2i GetClosestPoint(sf::Vector2f coord) const;

			bool PlayWhiteAt(sf::Vector2i point);
			bool PlayBlackAt(sf::Vector2i point);

			bool PlayWhiteAt(sf::Vector2f coord);
			bool PlayBlackAt(sf::Vector2f coord);

			void Reset();

			void SetLimitless(bool limitless);
			bool IsLimitless();

			unsigned GetStartSize() const;
			void SetStartSize(unsigned startSize);

			unsigned GetSize() const;

			sf::FloatRect GetLocalBounds() const;
			sf::FloatRect GetGameBounds() const;

			bool IsPlaying() const;
			bool WhitesWon() const;
			bool BlacksWon() const;
			bool GameWon() const;

			sf::Vector2i GetLast();

		private:
			bool hadGrowth = false;
			unsigned mStartSize;
			unsigned mTurn = 0;
			int mState = 0;
			Grid<GameObject> mGrid = Grid<GameObject>(0, 0, Free, Nil);

			bool PlayAt(GameObject object, sf::Vector2i point, bool force = false);
			bool CheckVictory(sf::Vector2i point, bool white) const;
			std::vector<Node<GameObject>> GetPlayableNodes() const;

			sf::Vector2i mLast;
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}