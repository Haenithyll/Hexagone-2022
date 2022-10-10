#pragma once
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Drawable.hpp"

namespace gk
{ 
	template <class T> struct Node
	{
		T value;
		sf::Vector2i point;

		Node(T value, sf::Vector2i point) : value(value), point(point) {};

		bool operator== (const Node<T>& other) const
		{
			return other.value == value && other.point == point;
		}

		bool operator!= (const Node<T>& other) const
		{
			return other.value != value || other.point != point;
		}
	};

	template <class T> class Grid : public sf::Drawable
	{
		public:
			Grid(unsigned size, unsigned gap, T defaultValue, T nilValue, sf::Color color = sf::Color::Black)
			{
				mSize = size;
				mGap = gap;

				mDefaultValue = defaultValue;
				mNilValue = nilValue;

				mColor = color;
			}

			unsigned GetSize() const
			{
				return mSize;
			}

			void SetSize(unsigned size)
			{
				mSize = size;
			}

			unsigned GetGap() const
			{
				return mGap;
			}

			void SetGap(unsigned gap)
			{
				mGap = gap;
			}

			bool IsLimitless()
			{
				return mLimitless;
			}

			void SetLimitless(bool limitless)
			{
				mLimitless = limitless;
			}

			sf::Color GetColor()
			{
				return mColor;
			}

			void SetColor(sf::Color color)
			{
				mColor = color;
			}

			sf::FloatRect GetLocalBounds() const
			{
				return sf::FloatRect(0.f, 0.f, (mSize - 1.f) * (mGap + 1.f), (mSize - 1.f) * (mGap + 1.f));
			}

			sf::Vector2i GetClosestPoint(sf::Vector2f coord) const
			{
				return sf::Vector2i(coord.x < (mGap + 1.f) / 2.f && coord.x >(mGap + 1.f) / -2.f ? 0 : (int)(coord.x / (mGap + 1.f) + (coord.x < 0.f ? -0.5 : 0.5)),
									coord.y < (mGap + 1.f) / 2.f && coord.y >(mGap + 1.f) / -2.f ? 0 : (int)(coord.y / (mGap + 1.f) + (coord.y < 0 ? -0.5 : 0.5)));
			}

			Node<T> GetClosestNode(sf::Vector2f coord) const
			{
				return GetNode(GetClosestPoint(coord));
			}

			Node<T> GetNode(sf::Vector2i point) const
			{
				if (GetNodeIndex(point) < 0) return mLimitless || ContainsPoint(point) ? Node<T>(mDefaultValue, point) : Node<T>(mNilValue, point);
				else return mNodes[GetNodeIndex(point)];
			}

			const std::vector<Node<T>>& GetNonDefaultNodes() const
			{
				return mNodes;
			}

			void SetNode(sf::Vector2i point, T value)
			{
				if (ContainsPoint(point))
				{
					for (int i = 0; i < mNodes.size(); i++)
					{
						if (mNodes[i].point == point) mNodes[i].value = value;
					}

					mNodes.push_back(Node<T>(value, point));
				}
			}

			void MoveAllNodes(sf::Vector2i direction)
			{
				for (int i = 0; i < mNodes.size(); i++)
				{
					if (ContainsPoint(mNodes[i].point + direction))
					{
						mNodes[i].point += direction;
					}
					else mNodes.erase(mNodes.begin() + i--);
				}
			}

			void Reset()
			{
				mNodes.clear();
			}

			sf::Vector2f GetNodeCoordinates(Node<T> node) const
			{
				return sf::Vector2f(node.point.x * (mGap + 1.f), node.point.y * (mGap + 1.f));
			}

			int PopulationByRadius(sf::Vector2i point, T value, int radius = 1, bool includePoint = false) const
			{
				int r = 0;

				for (int i = -radius, j; i <= radius; i++)
				{
					for (j = -radius; j <= radius; j++)
					{
						if (includePoint || (i != 0 || j != 0)) if (GetNode(sf::Vector2i(point.x + i, point.y + j)).value == value) r++;
					}
				}

				return r;
			}

			bool ContainsPoint(sf::Vector2i point) const
			{
				return point.x >= 0 && point.x < (int)mSize && point.y >= 0 && point.y < (int)mSize;
			}

		private:
			bool mLimitless = true;
			T mDefaultValue, mNilValue;
			unsigned mSize = 5, mGap;
			sf::Color mColor;

			std::vector<Node<T>> mNodes;

			int GetNodeIndex(sf::Vector2i point) const
			{
				for (int i = 0; i < mNodes.size(); i++) if (mNodes[i].point == point) return i;
				return -1;
			}

			void draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				sf::Vertex line[2];

				unsigned i;
				for (i = 0; i < mSize; i++)
				{
					line[0] = sf::Vertex(sf::Vector2f(i * (mGap + 1.f), 0.f), mColor);
					line[1] = sf::Vertex(sf::Vector2f(i * (mGap + 1.f), (mSize - 1.f) * (mGap + 1.f)), mColor);

					target.draw(line, 2, sf::Lines);

					line[0] = sf::Vertex(sf::Vector2f(0.f, i * (mGap + 1.f)), mColor);
					line[1] = sf::Vertex(sf::Vector2f((mSize - 1.f) * (mGap + 1.f), i * (mGap + 1.f)), mColor);

					target.draw(line, 2, sf::Lines);
				}
			}
	};
}