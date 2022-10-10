#include "Gomoku.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>

namespace gk
{
	Gomoku::Gomoku(unsigned startSize, unsigned gap)
	{
		mStartSize = startSize;

		mGrid.SetSize(startSize);
		mGrid.SetGap(gap);
	}

	sf::Vector2i Gomoku::GetClosestPoint(sf::Vector2f coord) const
	{
		return mGrid.GetClosestPoint(coord);
	}

	bool Gomoku::PlayWhiteAt(sf::Vector2i point)
	{
		return mTurn % 2 == 0 ? PlayAt(White, point) : false;
	}

	bool Gomoku::PlayBlackAt(sf::Vector2i point)
	{
		return mTurn % 2 == 1 ? PlayAt(Black, point) : false;
	}

	bool Gomoku::PlayWhiteAt(sf::Vector2f coord)
	{
		return mTurn % 2 == 0 ? PlayAt(White, mGrid.GetClosestPoint(coord)) : false;
	}

	bool Gomoku::PlayBlackAt(sf::Vector2f coord)
	{
		return mTurn % 2 == 1 ? PlayAt(Black, mGrid.GetClosestPoint(coord)) : false;
	}

	void Gomoku::Reset()
	{
		mTurn = 0;
		mState = 0;
		mGrid.SetSize(mStartSize);
		mGrid.Reset();
		PlayAt(mTurn % 2 == 0 ? White : Black, GetPlayableNodes()[0].point, true);
	}

	void Gomoku::SetLimitless(bool limitless)
	{
		mGrid.SetLimitless(limitless);
	}

	bool Gomoku::IsLimitless()
	{
		return mGrid.IsLimitless();
	}

	unsigned Gomoku::GetStartSize() const
	{
		return mStartSize;
	}

	void Gomoku::SetStartSize(unsigned startSize)
	{
		mStartSize = startSize;
	}

	unsigned Gomoku::GetSize() const
	{
		return mGrid.GetSize();
	}

	sf::FloatRect Gomoku::GetLocalBounds() const
	{
		return sf::FloatRect();
	}

	sf::FloatRect Gomoku::GetGameBounds() const
	{
		return sf::FloatRect(mGrid.GetLocalBounds().left - mGrid.GetGap() / 2, mGrid.GetLocalBounds().top - mGrid.GetGap() / 2, mGrid.GetLocalBounds().width + mGrid.GetGap(), mGrid.GetLocalBounds().height + mGrid.GetGap());
	}

	bool Gomoku::IsPlaying() const
	{
		return mState == 0;
	}

	bool Gomoku::WhitesWon() const
	{
		return mState == 1;
	}

	bool Gomoku::BlacksWon() const
	{
		return mState == 2;
	}

	bool Gomoku::GameWon() const
	{
		return mState != 0;
	}

	sf::Vector2i Gomoku::GetLast()
	{
		return mLast;
	}

	bool Gomoku::PlayAt(GameObject object, sf::Vector2i point, bool force)
	{
		Node<GameObject> node = mGrid.GetNode(point);

		if ((mGrid.ContainsPoint(node.point) && node.value == Free && (mGrid.PopulationByRadius(node.point, White) > 0 || mGrid.PopulationByRadius(node.point, Black) > 0)) || force)
		{
			mLast = node.point;
			mGrid.SetNode(node.point, object), mTurn++;

			if (CheckVictory(point, object == White)) mState = (object == White ? 1 : 2);

			if ((node.point.x == 0 || node.point.x == mGrid.GetSize() - 1 || node.point.y == 0 || node.point.y == mGrid.GetSize() - 1) && IsLimitless())
			{
				mGrid.SetSize(mGrid.GetSize() + 2u);
				mGrid.MoveAllNodes(sf::Vector2i(1, 1));
				mLast += sf::Vector2i(1, 1);
				hadGrowth = true;
			}
			else
			{
				hadGrowth = false;
			}

			return true;
		}

		return false;
	}

	bool Gomoku::CheckVictory(sf::Vector2i point, bool white) const
	{
		for (int i = -4, h = 0, dl = 0, v = 0, dr = 0; i <= 4; i++)
		{
			h = mGrid.GetNode(sf::Vector2i(point.x + i, point.y)).value == (white ? White : Black) ? h + 1 : 0;
			v = mGrid.GetNode(sf::Vector2i(point.x, point.y + i)).value == (white ? White : Black) ? v + 1 : 0;
			dl = mGrid.GetNode(sf::Vector2i(point.x + i, point.y + i)).value == (white ? White : Black) ? dl + 1 : 0;
			dr = mGrid.GetNode(sf::Vector2i(point.x - i, point.y + i)).value == (white ? White : Black) ? dr + 1 : 0;

			if (h >= 5 || dl >= 5 || v >= 5 || dr >= 5) return true;
		}

		return false;
	}

	std::vector<Node<GameObject>> Gomoku::GetPlayableNodes() const
	{
		if (mGrid.GetNonDefaultNodes().empty()) return {Node<GameObject>(Free, sf::Vector2i(mGrid.GetSize() / 2, mGrid.GetSize() / 2))};

		std::vector<Node<GameObject>> rtn;

		int i, j;
		Node<GameObject> current(Nil, sf::Vector2i(0, 0));
		for (auto node = mGrid.GetNonDefaultNodes().begin(); node != mGrid.GetNonDefaultNodes().end(); ++node)
		{
			for (i = -1; i <= 1; i++)
			{
				for (j = -1; j <= 1; j++)
				{
					current = mGrid.GetNode(sf::Vector2i(node->point.x + i, node->point.y + j));
					if (current.value == Free && std::all_of(rtn.begin(), rtn.end(), [current](Node<GameObject> n) { return n != current; }))
						rtn.push_back(current);
				}
			}
		}

		return rtn;
	}

	void Gomoku::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mGrid);

		sf::CircleShape pawn(mGrid.GetGap() / 2.f);
		pawn.setOutlineThickness(mGrid.GetGap() / -2.5f);
		pawn.setOrigin(pawn.getRadius(), pawn.getRadius());

		for (gk::Node<GameObject> node : mGrid.GetNonDefaultNodes())
		{
			if (node.value == White) pawn.setOutlineColor(sf::Color::White), pawn.setFillColor(sf::Color::White);
			else if (node.value == Black) pawn.setOutlineColor(sf::Color::Black), pawn.setFillColor(sf::Color::Black);

			if (node.point == mLast) pawn.setFillColor(node.value == White ? sf::Color::Black : sf::Color::White);
			pawn.setPosition(mGrid.GetNodeCoordinates(node));
			target.draw(pawn);
		}

		if (mTurn % 2 == 0) pawn.setOutlineColor(sf::Color::White), pawn.setFillColor(sf::Color(255, 255, 255, 25));
		else pawn.setOutlineColor(sf::Color::Black), pawn.setFillColor(sf::Color(0, 0, 0, 25));
		pawn.setOutlineThickness(0.f);

		for (gk::Node<GameObject> node : GetPlayableNodes())
		{
			pawn.setPosition(mGrid.GetNodeCoordinates(node));
			target.draw(pawn);
		}
	}
}