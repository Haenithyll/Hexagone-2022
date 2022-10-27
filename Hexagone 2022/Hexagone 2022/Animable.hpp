#pragma once

#include "SFML/System/Vector2.hpp"

#include <string>

#define ANIMATION_FRAME_DELAY 0.05f
#define RAD_TO_DEG 57.2957795131f

class Animable
{
	public:
		Animable(int count = 1, int offset = 0);

		virtual void Update(float deltaTime);

		void MoveTo(sf::Vector2f position, float delay = 0.f);

	protected:
		int mCount;
		int mIndex;

		float mTime = 0.f;

		const sf::Vector2f& GetDrawPosition() const;
		float GetDrawRotation() const;

		bool IsMoving() const;

	private:
		float ComputeLength(const sf::Vector2f& vector);
		float ComputeDistance(const sf::Vector2f& a, const sf::Vector2f& b);

		sf::Vector2f mMoveDirection;
		sf::Vector2f mCurrentPosition;

		float mBaseDistance;
		float mRemainingDistance;
		float mMoveDelay;

		float mMoveRotation;
		float mCurrentRotation;
};
