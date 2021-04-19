#pragma once
#include "BridgeShooter.h"

class Image;
class Animation
{
private:
	bool isLoop;
	float frame;
	int fps;
	Image* lpImage;

public:
	void Change(string imageKey, int fps, bool isLoop = true, bool isReset = false);
	void Update(float deltaTime);
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, float angle);
};

