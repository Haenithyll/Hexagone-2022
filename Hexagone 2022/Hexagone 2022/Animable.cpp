#include "Animable.hpp"

#include "TextureManager.hpp"

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
}
