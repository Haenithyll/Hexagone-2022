#pragma once
#include <cmath>
#include <vector>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Clock.hpp"

namespace sw
{
	enum Unit
	{
		Pixel,
		Percent
	};

	enum Reference
	{
		World,
		Parent
	};

	enum Origin
	{
		Center,
		Top,
		Down,
		Left,
		Right,
		TopLeft,
		TopRight,
		DownLeft,
		DownRight
	};

	class Drawable : public sf::Drawable
	{
		private:
			sf::Vector2f ClampVector(const sf::Vector2f& vector, float min, float max) const;
			float MoveToward(float a, float b, float t);

		#pragma region Transform

		public:
			void SetTransform(Origin origin, Unit unit, Reference reference);

			Unit GetUnit() const;
			void SetUnit(Unit unit);

			Reference GetReference() const;
			void SetReference(Reference reference);

			Origin GetOrigin() const;
			void SetOrigin(Origin origin);

			const sf::Vector2f& GetPosition() const;
			void SetPosition(const sf::Vector2f& position);
			void SetPosition(float posX, float posY);

			const sf::Vector2f& GetSize() const;
			void SetSize(const sf::Vector2f& size);
			void SetSize(float width, float height);

		private:
			sf::Vector2f mPosition;
			sf::Vector2f mSize;

			Unit mUnit = Percent;
			Reference mReference = Parent;
			Origin mOrigin = Center;

			sf::Vector2f GetTruePosition(Origin origin, bool global = true) const;

			virtual const sf::Vector2f& GetTruePosition() const = 0;
			virtual void SetTruePosition(const sf::Vector2f& position) = 0;

			virtual const sf::Vector2f& GetTrueOrigin() const = 0;
			virtual void SetTrueOrigin(const sf::Vector2f& origin) = 0;

			virtual sf::Vector2f GetTrueSize() const = 0;
			virtual void SetTrueSize(const sf::Vector2f& size) = 0;

		protected:
			void UpdatePosition();
			void UpdateSize();

			virtual sf::FloatRect GetLocalBounds() const = 0;
			virtual sf::FloatRect GetGlobalBounds() const = 0;

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		#pragma endregion
	
		#pragma region Hierarchy

		public:
			bool HasParent() const;
			bool HasChild() const;
			unsigned GetChildCount() const;
			bool IsChild(Drawable* child) const;

			Drawable* GetParent() const;
			void SetParent(Drawable* object);

			Drawable* GetChild(int index) const;
			void AddChild(Drawable* child);
			void DeleteChild(int index);
			void DeleteChild(Drawable* child);

		private:
			Drawable* mParent = nullptr;
			std::vector<Drawable*> mChildren;

		#pragma endregion

		#pragma region Color

		public:
			virtual sf::Color GetFillColor() const = 0;
			virtual void SetFillColor(const sf::Color& color) = 0;

			virtual sf::Color GetOutlineColor() const = 0;
			virtual void SetOutlineColor(const sf::Color& color) = 0;

			void AlphaOverLifeTime(float period, unsigned char min, unsigned char max);

			void FadeIn(float delay, float dt);
			void FadeOut(float delay, float dt);

		private:
			sf::Clock mClock;

			virtual unsigned char GetGlobalAlpha();
			virtual void SetGlobalAlpha(unsigned char alpha);

		#pragma endregion
	};
}