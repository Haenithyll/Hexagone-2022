#include "Animable.hpp"
#include "Log.hpp"

Animable::Movement::Movement(sf::Vector2f start, sf::Vector2f end, float delay)
{
	Position = end;

	Direction = end - start;

	Distance = sqrtf(powf(Direction.x, 2.f) + powf(Direction.y, 2.f));

	Direction /= Distance;

	Duration = delay;

	Rotation = -atan2f(-Direction.y, Direction.x) * RAD_TO_DEG + 90.f;
}

Animable::Animable(int count, int offset)
{
	mCount = count;
	mIndex = offset % count;

	mMovements = std::queue<Movement>();
}

void Animable::Update(float deltaTime)
{
	mTime += deltaTime;

	if (mTime >= ANIMATION_FRAME_DELAY)
	{
		mIndex = (mIndex + 1) % mCount;
		
		mTime = fmod(mTime, ANIMATION_FRAME_DELAY);
	}

	if (mRemainingDistance > 0)
	{
		float distance = mBaseDistance * deltaTime / mMoveDelay;

		mCurrentPosition += mMoveDirection * distance;

		mRemainingDistance -= distance;
	}
	else
	{
		mCurrentPosition = mTargetPosition;

		if (!mMovements.empty())
		{
			Movement movement = mMovements.front();

			mMoveDirection = movement.Direction;
			mBaseDistance = movement.Distance;
			mMoveDelay = movement.Duration;
			mMoveRotation = movement.Rotation;
			mTargetPosition = movement.Position;

			if (mMoveDelay <= 0.f)
			{
				mCurrentPosition = movement.Position;

				mRemainingDistance = 0.f;

				mCurrentRotation = mMoveRotation;
			}
			else
				mRemainingDistance = mBaseDistance;

			mMovements.pop();
		}
	}

	mCurrentRotation = std::lerp(mCurrentRotation, mMoveRotation, deltaTime * 10.f);
}

void Animable::MoveTo(sf::Vector2f position, float delay)
{
	sf::Vector2f start = mMovements.empty() ? mCurrentPosition : mMovements.back().Position;

	mMovements.push(Movement(start, position, delay));
}

const sf::Vector2f& Animable::GetDrawPosition() const
{
	return mCurrentPosition;
}

float Animable::GetDrawRotation() const
{
	return mCurrentRotation;
}

bool Animable::IsMoving() const
{
	return mRemainingDistance > 0.f;
}
