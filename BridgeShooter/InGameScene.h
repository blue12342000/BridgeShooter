#pragma once
#include "BridgeShooter.h"
#include <vector>

class Unit;
class Item;
class Image;
class InGameScene
{
private:
	vector<Unit*> vEnemys;
	vector<Item*> vItems;
	Unit* lpPlayer;
	Unit* lpPlanet;

	Image* lpBackBuffer;
	Image* lpBackImage;		//���
	Image* lpBackImage2;	//��ũ�ѿ� ���
	int frame;
	float elapsedTime;
	Unit* lpPlanetSSJ;

	float backgroundMover;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
};

