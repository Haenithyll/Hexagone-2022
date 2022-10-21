#pragma once
#include "SFML/Graphics/View.hpp"

namespace sw
{
	class View
	{
		public:
			View();
			View(const sf::View& view);
			View(const sf::FloatRect& rect);
			View(const sf::Vector2f& center, const sf::Vector2f& size);

			float GetZoom() const;
			void SetMinZoom(float min);
			void SetMaxZoom(float max);
			void Zoom(float factor);

			const sf::Vector2f& GetCenter() const;
			void SetCenter(float x, float y, bool keepTransform = false);
			void SetCenter(const sf::Vector2f& center, bool keepTransform = false);

			const sf::Vector2f& GetSize() const;
			void SetSize(float width, float height, bool keepTransform = false);
			void SetSize(const sf::Vector2f& size, bool keepTransform = false);

			void Move(float x, float y);
			void Move(sf::Vector2f offset);

			void SetViewport(float left, float top, float width, float height);
			void SetViewport(const sf::FloatRect& rect);
			sf::Vector2f SetScaleViewport(float left, float top, float width, float height, bool inverted = false);
			sf::Vector2f SetScaleViewport(const sf::FloatRect& rect, bool inverted = false);

			sf::FloatRect GetLocalBounds();
			sf::FloatRect GetViewBounds();

			operator const sf::View&();

			void LockPosition();
			void SetAutoLock(bool autoLock);

		private:
			sf::View mView;

			sf::Vector2u mWindowSize;
			float mZoom = 1, mZoomMin = 0.5, mZoomMax = 2;
			sf::Vector2f mOffset = sf::Vector2f(0, 0);
			sf::Vector2f mDefaultCenter;
			sf::Vector2f mDefaultSize;
			bool mAutoLock = false;
	};
}