#pragma once

#include <SDL/SDL_timer.h>

class DeltaTime
{

	public:

		DeltaTime();
		~DeltaTime();

		void Update();

		float GetDeltaTime() const;

	private:

		float m_deltaTime;
		float lastTicks = 0.0f;
		float currentTicks = 0.0f;

};