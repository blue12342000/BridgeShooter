#include "Factory.h"

void Factory::Update(float deltaTime)
{
	for (auto& pair : mTimeCheck)
	{
		pair.second.isChanged = false;
		if (pair.second.nextTime <= elapsedTime)
		{
			pair.second.nextTime = elapsedTime + ((float)pair.first / 1000);
			pair.second.isChanged = true;
		}
	}
	elapsedTime += deltaTime;
}
