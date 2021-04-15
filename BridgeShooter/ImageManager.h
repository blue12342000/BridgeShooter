#pragma once
#include "BridgeShooter.h"
#include "Singleton.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*> mImageDatas;

public:
	HRESULT Init();
	void Release();

	//이미지 출력
	Image* AddImage(string key, const char* fileName,
		int width, int height, bool isTransparent = FALSE,
		COLORREF transColor = FALSE);


	Image* AddImage(string key, const char* fileName,
		int width, int height, int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	void DeleteImage(string key);
	Image* FindImage(string key);

};

