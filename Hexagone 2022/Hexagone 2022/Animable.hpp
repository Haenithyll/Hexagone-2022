#pragma once

#include "SFML/System/Vector2.hpp"

#include <string>
#include <queue>

#define ANIMATION_FRAME_DELAY 0.05f
#define RAD_TO_DEG 57.2957795131f

class Animable
{
	private:
		struct Movement
		{
			sf::Vector2f Position;
			sf::Vector2f Direction;

			float Distance;
			float Duration;
			float Rotation;

			Movement(sf::Vector2f start, sf::Vector2f end, float delay);
		};

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

		std::queue<Movement> mMovements;

		sf::Vector2f mMoveDirection;
		sf::Vector2f mCurrentPosition;
		sf::Vector2f mTargetPosition;

		float mBaseDistance;
		float mRemainingDistance;
		float mMoveDelay;

		float mMoveRotation;
		float mCurrentRotation;
};
