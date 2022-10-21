#include "View.hpp"
#include "Window.hpp"
#include <iostream>

namespace sw
{
	View::View()
	{
		mWindowSize = Window::Main()->GetSize();
		mDefaultCenter = mView.getCenter();
		mDefaultSize = mView.getSize();
	}

	View::View(const sf::View& view)
	{
		mView = view;

		mWindowSize = Window::Main()->GetSize();
		mDefaultCenter = mView.getCenter();
		mDefaultSize = mView.getSize();
	}

	View::View(const sf::FloatRect& rect)
	{
		mView = sf::View(rect);

		mWindowSize = Window::Main()->GetSize();
		mDefaultCenter = mView.getCenter();
		mDefaultSize = mView.getSize();
	}

	View::View(const sf::Vector2f& center, const sf::Vector2f& size)
	{
		mView = sf::View(center, size);

		mWindowSize = Window::Main()->GetSize();
		mDefaultCenter = mView.getCenter();
		mDefaultSize = mView.getSize();
	}

	float View::GetZoom() const
	{
		return mZoom;
	}

	void View::SetMinZoom(float min)
	{
		mZoomMin = min;
	}

	void View::SetMaxZoom(float max)
	{
		mZoomMax = max;
	}
	
	void View::Zoom(float factor)
	{
		if ((mZoom < mZoomMax && factor > 1) || (mZoom > mZoomMin && factor < 1)) mView.zoom(factor), mZoom *= factor;
		if (mAutoLock) LockPosition();
	}

	const sf::Vector2f& View::GetCenter() const
	{
		return mView.getCenter();
	}

	void View::SetCenter(float x, float y, bool keepTransform)
	{
		mView.setCenter(x, y);
		mDefaultCenter = sf::Vector2f(x, y);
		if (keepTransform) mView.move(mOffset);
		if (mAutoLock) LockPosition();
	}

	void View::SetCenter(const sf::Vector2f& center, bool keepTransform)
	{
		mView.setCenter(center);
		mDefaultCenter = center;
		if (keepTransform) mView.move(mOffset);
		if (mAutoLock) LockPosition();
	}

	const sf::Vector2f& View::GetSize() const
	{
		return mView.getSize();
	}

	void View::SetSize(float width, float height, bool keepTransform)
	{
		mView.setSize(width, height);
		mDefaultSize = sf::Vector2f(width, height);
		if (keepTransform) mView.zoom(mZoom);
	}

	void View::SetSize(const sf::Vector2f& size, bool keepTransform)
	{
		mView.setSize(size);
		mDefaultSize = size;
		if (keepTransform) mView.zoom(mZoom);
	}

	void View::Move(float x, float y)
	{
		mView.move(x, y);
		mOffset += sf::Vector2f(x, y);
		if (mAutoLock) LockPosition();
	}

	void View::Move(sf::Vector2f offset)
	{
		mView.move(offset);
		mOffset += offset;
		if (mAutoLock) LockPosition();
	}

	void View::SetViewport(float left, float top, float width, float height)
	{
		mView.setViewport(sf::FloatRect(left, top, width, height));
	}

	void View::SetViewport(const sf::FloatRect& rect)
	{
		mView.setViewport(rect);
	}

	sf::Vector2f View::SetScaleViewport(float left, float top, float width, float height, bool inverted)
	{
		float ratio;

		sf::Vector2f scale;

		if (mWindowSize.x > mWindowSize.y)
		{
			ratio = (float)mWindowSize.y / (float)mWindowSize.x;

			if (inverted)
			{
				height /= ratio;

				scale = sf::Vector2f(0.f, ratio);
			}
			else
			{
				width *= ratio;

				scale = sf::Vector2f(ratio, 1.f);
			}
		}
		else
		{
			ratio = (float)mWindowSize.x / (float)mWindowSize.y;

			if (inverted)
			{
				width /= ratio;

				scale = sf::Vector2f(ratio, 0.f);
			}
			else
			{
				height *= ratio;

				scale = sf::Vector2f(1.f, ratio);
			}
		}
		
		mView.setViewport(sf::FloatRect(left, top, width, height));

		return scale;
	}

	sf::Vector2f View::SetScaleViewport(const sf::FloatRect& rect, bool inverted)
	{
		return SetScaleViewport(rect.left, rect.top, rect.width, rect.height, inverted);
	}

	sf::FloatRect View::GetLocalBounds()
	{
		return sf::FloatRect(sf::Vector2f(mView.getViewport().left * mWindowSize.x, mView.getViewport().top * mWindowSize.y),
								sf::Vector2f(mView.getViewport().width * mWindowSize.x, mView.getViewport().height * mWindowSize.y));
	}

	sf::FloatRect View::GetViewBounds()
	{
		return sf::FloatRect(mView.getCenter().x - mView.getSize().x / 2, mView.getCenter().y - mView.getSize().y / 2, mView.getSize().x, mView.getSize().y);
	}

	View::operator const sf::View& ()
	{
		return mView;
	}

	void View::LockPosition()
	{
		if (GetViewBounds().left < mDefaultCenter.x - mDefaultSize.x / 2.f)
			mView.move(-(GetViewBounds().left - mDefaultCenter.x + mDefaultSize.x / 2.f), 0.f);

		if (GetViewBounds().left + GetViewBounds().width > mDefaultCenter.x + mDefaultSize.x / 2.f)
			mView.move(-(GetViewBounds().left + GetViewBounds().width - mDefaultCenter.x - mDefaultSize.x / 2.f), 0.f);

		if (GetViewBounds().top < mDefaultCenter.y - mDefaultSize.y / 2.f)
			mView.move(0.f, -(GetViewBounds().top - mDefaultCenter.y + mDefaultSize.y / 2.f));

		if (GetViewBounds().top + GetViewBounds().height > mDefaultCenter.y + mDefaultSize.y / 2.f)
			mView.move(0.f, -(GetViewBounds().top + GetViewBounds().height - mDefaultCenter.y - mDefaultSize.y / 2.f));

		mOffset = mView.getCenter() - mDefaultCenter;

		if (GetZoom() > 1) mView.setCenter(mDefaultCenter.x, mDefaultCenter.y);
	}

	void View::SetAutoLock(bool autoLock)
	{
		mAutoLock = autoLock;
	}
}