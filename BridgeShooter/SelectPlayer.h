#pragma once
#include "GameScene.h"

class Image;
class SelectPlayer : public GameScene
{
private:

	Image* lpBackImage;
	Image* lpBackBuffer;

	vector<Image*> vLpPlayerImg; 
	
	RECT selectBox;
	int selectIndex;
	bool hasSelected;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);

};

