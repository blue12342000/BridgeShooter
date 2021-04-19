#pragma once
#include "BridgeShooter.h"

class Image;
class ProgressBar
{
private:
	int count;
	Image* lpImage;
public:
	void CreateProgressBar(string imageKey);
	void Update(float deltaTime);
	void Render(HDC hdc, int X, int Y);
};
