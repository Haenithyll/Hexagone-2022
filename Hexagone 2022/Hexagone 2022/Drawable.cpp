#include "Drawable.hpp"
#include "Window.hpp"

#include <iostream>
#include <limits>

namespace sw
{
	sf::Vector2f Drawable::ClampVector(const sf::Vector2f& vector, float min, float max = std::numeric_limits<float>::max()) const
	{
		
		return sf::Vector2f(fmaxf(min, fminf(vector.x, max)), fmaxf(min, fminf(vector.y, max)));
	}

	float Drawable::MoveToward(float a, float b, float t)
	{
		if (abs(b - a) <= t) return b;
		else return a + (a > b ? -1 : 1) * t;
	}

	#pragma region Transform

	void Drawable::SetTransform(Origin origin, Unit unit, Reference reference)
	{
		SetOrigin(origin);
		SetUnit(unit);
		SetReference(reference);

		UpdateSize();
		UpdatePosition();
	}

	Unit Drawable::GetUnit() const
	{
		return mUnit;
	}

	void Drawable::SetUnit(Unit unit)
	{
		mUnit = unit;

		UpdateSize();
		UpdatePosition();
	}

	Reference Drawable::GetReference() const
	{
		return mReference;
	}

	void Drawable::SetReference(Reference reference)
	{
		mReference = reference;

		UpdateSize();
		UpdatePosition();
	}

	Origin Drawable::GetOrigin() const
	{
		return mOrigin;
	}

	void Drawable::SetOrigin(Origin origin)
	{
		mOrigin = origin;

		UpdateSize();
		UpdatePosition();
	}

	const sf::Vector2f& Drawable::GetPosition() const
	{
		return mPosition;
	}

	void Drawable::SetPosition(const sf::Vector2f& position)
	{
		mPosition = position;

		UpdateSize();
		UpdatePosition();
	}

	void Drawable::SetPosition(float posX, float posY)
	{
		mPosition = sf::Vector2f(posX, posY);

		UpdateSize();
		UpdatePosition();
	}

	const sf::Vector2f& Drawable::GetSize() const
	{
		return mSize;
	}

	void Drawable::SetSize(const sf::Vector2f& size)
	{
		mSize = size;

		UpdateSize();
		UpdatePosition();
	}

	void Drawable::SetSize(float width, float height)
	{
		mSize = sf::Vector2f(width, height);

		UpdateSize();
		UpdatePosition();
	}

	sf::Vector2f sw::Drawable::GetOriginPosition(Origin origin, bool global) const
	{
		sf::FloatRect rect = global ? GetGlobalBounds() : GetLocalBounds();

		switch (mOrigin)
		{
			case Center:
				return sf::Vector2f(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);

			case Top:
				return sf::Vector2f(rect.left + rect.width / 2.f, rect.top);

			case Down:
				return sf::Vector2f(rect.left + rect.width / 2.f, rect.top + rect.height);

			case Left:
				return sf::Vector2f(rect.left, rect.top + rect.height / 2.f);

			case Right:
				return sf::Vector2f(rect.left + rect.width, rect.top + rect.height / 2.f);

			case TopLeft:
				return sf::Vector2f(rect.left, rect.top);

			case TopRight:
				return sf::Vector2f(rect.left + rect.width, rect.top);

			case DownLeft:
				return sf::Vector2f(rect.left, rect.top + rect.height);

			case DownRight:
				return sf::Vector2f(rect.left + rect.width, rect.top + rect.height);

			default:
				return GetTruePosition();
		}
	}

	void Drawable::UpdatePosition()
	{
		SetTrueOrigin(GetOriginPosition(mOrigin, false));

		if (mReference == Reference::Parent && HasParent())
		{
			if (mUnit == Unit::Pixel)
			{
				SetTruePosition(mPosition + GetParent()->GetOriginPosition(TopLeft));
			}
			else
			{
				sf::Vector2f parentSize = sf::Vector2f(GetParent()->GetGlobalBounds().width, GetParent()->GetGlobalBounds().height);
				sf::Vector2f parentPosition = sf::Vector2f(GetParent()->GetGlobalBounds().left, GetParent()->GetGlobalBounds().top);

				sf::Vector2f worldPos = ClampVector(mPosition, 0.f) / 100.f;
				worldPos.x *= parentSize.x, worldPos.y *= parentSize.y;

				SetTruePosition(worldPos + parentPosition);
			}
		}
		else
		{
			if (mUnit == Pixel || Window::Main() == nullptr)
			{
				SetTruePosition(mPosition);
			}
			else
			{
				sf::Vector2f worldPos = ClampVector(mPosition, 0.f) / 100.f;
				worldPos.x *= Window::Main()->GetSize().x, worldPos.y *= Window::Main()->GetSize().y;
				SetTruePosition(worldPos);
			}
		}

		for (unsigned i = 0; i < GetChildCount(); i++)
		{
			GetChild(i)->UpdateSize();
			GetChild(i)->UpdatePosition();
		}
	}

	void Drawable::UpdateSize()
	{
		if (mUnit == Unit::Percent)
		{
			if (mReference == Reference::Parent && HasParent())
			{
				sf::Vector2f worldSize = ClampVector(mSize, 0.f) / 100.f;
				worldSize.x *= GetParent()->GetTrueSize().x, worldSize.y *= GetParent()->GetTrueSize().y;
				SetTrueSize(worldSize);
			}
			else if (Window::Main() != nullptr)
			{
				sf::Vector2f worldSize = ClampVector(mSize, 0.f) / 100.f;
				worldSize.x *= Window::Main()->GetSize().x, worldSize.y *= Window::Main()->GetSize().y;
				SetTrueSize(worldSize);
			}
			else SetTrueSize(mSize);
		}
		else SetTrueSize(mSize);

		for (unsigned i = 0; i < GetChildCount(); i++)
		{
			GetChild(i)->UpdateSize();
			GetChild(i)->UpdatePosition();
		}
	}

	#pragma endregion

	#pragma region Hierarchy

	bool Drawable::HasParent() const
	{
		return mParent != nullptr;
	}

	bool Drawable::HasChild() const
	{
		return mChildren.empty();
	}

	unsigned Drawable::GetChildCount() const
	{
		return static_cast<unsigned>(mChildren.size());
	}

	bool Drawable::IsChild(Drawable* child) const
	{
		for (unsigned i = 0; i < GetChildCount(); i++)
		{
			if (mChildren[i] == child) return true;
		}

		return false;
	}

	Drawable* Drawable::GetParent() const
	{
		return mParent;
	}

	void Drawable::SetParent(Drawable* object)
	{
		if (HasParent()) mParent->DeleteChild(this); // Je fugue

		if (object == nullptr) mParent = nullptr; // Si mon parent m'abandonne
		else if (!(object->IsChild(this))) // Si je ne suis pas déjà son enfant
		{
			mParent = object; // J'actualise mon parent

			mParent->AddChild(this); // Je le dis à mon nouveau parent
		}

		UpdatePosition();
		UpdateSize();
	}

	Drawable* Drawable::GetChild(int index) const
	{
		return (index >= 0 && index < (int)GetChildCount()) ? mChildren[index] : nullptr;
	}

	void Drawable::AddChild(Drawable* child)
	{
		if (child != nullptr)
		{
			if (!IsChild(child)) mChildren.push_back(child); // Si je ne l'ai pas j'ajoute l'enfant

			if (child->GetParent() != this) child->SetParent(this); // S'il ne le sait pas je lui dis

			child->UpdatePosition();
		}
	}

	void Drawable::DeleteChild(int index)
	{
		if (index >= 0 && index < (int)GetChildCount()) mChildren.erase(mChildren.begin() + index);
	}

	void Drawable::DeleteChild(Drawable* child)
	{
		if (IsChild(child))
		{
			child->SetParent(nullptr);

			mChildren.erase(std::find(mChildren.begin(), mChildren.end(), child));
		}
	}

	#pragma endregion

	#pragma region Color

		void Drawable::AlphaOverLifeTime(float period, unsigned char min, unsigned char max)
		{
			float amp = (max - min) / 2.f;
			SetGlobalAlpha((unsigned char) (amp * sin((2.f * 3.14f / period) * mClock.getElapsedTime().asSeconds()) + (float)min + amp));

			for (unsigned i = 0; i < GetChildCount(); i++)
				GetChild(i)->AlphaOverLifeTime(period, min, max);
		}

		void Drawable::FadeIn(float delay, float dt)
		{
			SetGlobalAlpha((unsigned char)MoveToward((float)GetGlobalAlpha(), 255.f, dt / delay / 0.002f));

			for (unsigned i = 0; i < GetChildCount(); i++) GetChild(i)->FadeIn(delay, dt);
		}

		void Drawable::FadeOut(float delay, float dt)
		{
			SetGlobalAlpha((unsigned char)MoveToward((float)GetGlobalAlpha(), 0.f, dt / delay / 0.002f));

			for (unsigned i = 0; i < GetChildCount(); i++) GetChild(i)->FadeOut(delay, dt);
		}

		unsigned char Drawable::GetGlobalAlpha()
		{
			return GetFillColor().a;
		}

		void Drawable::SetGlobalAlpha(unsigned char alpha)
		{
			sf::Color color = GetFillColor();
			color.a = alpha;
			SetFillColor(color);
			color = GetOutlineColor();
			color.a = alpha;
			SetOutlineColor(color);
		}

	#pragma endregion
}