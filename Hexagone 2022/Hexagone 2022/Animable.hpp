#pragma once

#include <string>

#define ANIMATION_FRAME_DELAY 0.05f

class Animable
{
	public:
		Animable(int count = 1, int offset = 0);

		virtual void Update(float deltaTime);

	protected:
		int mCount;
		int mIndex;

		float mTime = 0.f;
};
