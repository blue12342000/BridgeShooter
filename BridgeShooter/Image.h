#pragma once
#include "BridgeShooter.h"

class Image
{
public:
	enum IMAGE_LOAD_TYPE
	{
		RESOURCE,
		FILE,
		EMPTY,
		END
	};

	struct ImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBitmap;
		int width;
		int height;
		BYTE loadType;

		int maxFrameX;
		int maxFrameY;
		int totalFrame;

		bool isTransparent;
		COLORREF transColor;

		ImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_TYPE::EMPTY;

			maxFrameX = 0;
			maxFrameY = 0;
			totalFrame = 0;

			isTransparent = false;
			transColor = 0;
		};
	};

	struct BlendInfo
	{
		HDC hBlendDC;
		HBITMAP hBlendBit;
		BLENDFUNCTION blendFunc;
	};

private:
	ImageInfo* lpImageInfo;
	BlendInfo* lpBlendInfo;

public:
	HRESULT Init(int width, int height);
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);
	HRESULT Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, int totalFrame, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	void Render(HDC hdc, int destX = 0, int destY = 0, int frame = 0);
	void AlphaRender(HDC hdc, int destX, int destY);
	
	void Release();

	inline HDC GetMemDC()
	{
		if (lpImageInfo) return lpImageInfo->hMemDC;
		return NULL;
	}
};
