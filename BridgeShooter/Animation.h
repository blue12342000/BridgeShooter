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
	void Change(string imageKey, int fps, bool isLoop = true);
	void Update(float deltaTime);
	void Render(HDC hdc, int destX, int destY);
};

