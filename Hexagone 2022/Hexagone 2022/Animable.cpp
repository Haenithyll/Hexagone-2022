#include "Animable.hpp"
#include "Log.hpp"
Animable::Animable(int count, int offset)
{
	mCount = count;
	mIndex = offset % count;
}

void Animable::Update(float deltaTime)
{
	mTime += deltaTime;

	if (mTime >= ANIMATION_FRAME_DELAY)
	{
		mIndex = (mIndex + 1) % mCount;
		
		mTime = fmod(mTime, ANIMATION_FRAME_DELAY);
	}

	if (mRemainingDistance > 0.f)
	{
		float distance = mBaseDistance * deltaTime / mMoveDelay;

		mCurrentPosition += mMoveDirection * distance;

		mRemainingDistance -= distance;
	}

	mCurrentRotation = std::lerp(mCurrentRotation, mMoveRotation, deltaTime * 10.f);
}

void Animable::MoveTo(sf::Vector2f position, float delay)
{
	sf::Vector2f move = position - mCurrentPosition;
	
	mBaseDistance = ComputeLength(move);
	mMoveDelay = delay;

	mMoveDirection = move / mBaseDistance;

	mMoveRotation = -atan2f(-mMoveDirection.y, mMoveDirection.x) * RAD_TO_DEG + 90.f;

	if (delay <= 0.f)
	{
		mCurrentPosition = position;

		mRemainingDistance = 0.f;

		mCurrentRotation = mMoveRotation;
	}
	else
		mRemainingDistance = mBaseDistance;
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

float Animable::ComputeLength(const sf::Vector2f& vector)
{
	return sqrtf(powf(vector.x, 2.f) + powf(vector.y, 2.f));
}

float Animable::ComputeDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return ComputeLength(b - a);
}
