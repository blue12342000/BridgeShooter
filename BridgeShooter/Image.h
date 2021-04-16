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
	HRESULT Init(string fileName, int width, int height, bool isTransparent = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT Init(string fileName, int width, int height, int maxFrameX, int maxFrameY, int totalFrame, bool isTransparent = false, COLORREF transColor = RGB(255, 0, 255));

	HRESULT Reverse(const Image& target);

	void Render(HDC hdc, int destX = 0, int destY = 0, int frame = 0, UINT uFlag = U_IA_DEFAULT);
	void AlphaRender(HDC hdc, int destX, int destY);
	
	void Release();

	inline HDC GetMemDC() { return (lpImageInfo) ? lpImageInfo->hMemDC : NULL; }
	inline int GetTotalFrame() { return (lpImageInfo) ? lpImageInfo->totalFrame : 1; }
};
