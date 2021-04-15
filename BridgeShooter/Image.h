#pragma once
#include "BridgeShooter.h"

class Image
{
public:
	enum IMAGE_LOAD_TYPE
	{
		RESOURCE,		// 프로젝트 자체에 포함 시킬 이미지
		FILE,			// 외부에서 로드할 이미지
		EMPTY,			// 자체 생산 이미지
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// 리소스의 고유한 ID
		HDC hMemDC;			// 그리기를 주관하는 핸들
		HBITMAP hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		int width;			// 이미지 가로 크기
		int height;			// 이미지 세로 크기
		BYTE loadType;		// 로드 타입

		//알파블렌드 선언
		HDC hBlendDC;			// 알파-목적지
		HBITMAP hBlendBit;		// 알파-이미지정보
		HBITMAP hBlendOldBit;	// 알파-기존이미지 정보

		// 애니메이션 관련 (프레임데이터)
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_TYPE::EMPTY;

			//알파블렌드 용 변수
			hBlendDC = NULL;
			hBlendBit = NULL;
			hBlendOldBit = NULL;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, * LPIMAGE_INFO;	//이거 어떻게 안되나.

private:
	IMAGE_INFO* imageInfo;		// 이미지 정보 구조체 포인터
	bool isTransparent;
	COLORREF transColor;
	BLENDFUNCTION blendFunc;

public:
	// 빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// 화면에 출력
	void Render(HDC hdc, int destX = 0, int destY = 0, bool isCenterRenderring = FALSE);
	// 움직이는 이미지 출력
	void FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY);
	// 사라지는 이미지 출력
	void AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring);
	
	//(미구현)모자이크 : 이미지를 키웠다가 작은 해상도로 복사하면서 해상도 깨지는 방법으로 연출
	void MosaicRender(HDC hdc, int destX, int destY, bool isCenterRenderring = false);
	//(미구현)블러 : 색상 정보를 제한해서 비슷한 색끼리 같은 값으로 출력되도록 연출
	void BlurRender(HDC hdc, int destX, int destY, bool isCenterRenderring = false);



	void Release();

	// get, set
	HDC GetMemDC()
	{
		if (this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	}
	
	// 각 유닛안쪽에서 사라질때 호출
	BLENDFUNCTION* GetBlendFunc() { return &(this->blendFunc); }
};
