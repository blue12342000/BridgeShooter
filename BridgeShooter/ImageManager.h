#pragma once
#include "BridgeShooter.h"
#include "Singleton.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*> mLpImageDatas;

public:
	HRESULT Init();
	void Release();

	Image* FindImage(string key);
};

