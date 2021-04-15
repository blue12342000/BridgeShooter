#pragma once
#include "BridgeShooter.h"

class Image
{
public:
	enum IMAGE_LOAD_TYPE
	{
		RESOURCE,		// ������Ʈ ��ü�� ���� ��ų �̹���
		FILE,			// �ܺο��� �ε��� �̹���
		EMPTY,			// ��ü ���� �̹���
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// ���ҽ��� ������ ID
		HDC hMemDC;			// �׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int width;			// �̹��� ���� ũ��
		int height;			// �̹��� ���� ũ��
		BYTE loadType;		// �ε� Ÿ��

		//���ĺ��� ����
		HDC hBlendDC;			// ����-������
		HBITMAP hBlendBit;		// ����-�̹�������
		HBITMAP hBlendOldBit;	// ����-�����̹��� ����

		// �ִϸ��̼� ���� (�����ӵ�����)
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

			//���ĺ��� �� ����
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
	} IMAGE_INFO, * LPIMAGE_INFO;	//�̰� ��� �ȵǳ�.

private:
	IMAGE_INFO* imageInfo;		// �̹��� ���� ����ü ������
	bool isTransparent;
	COLORREF transColor;
	BLENDFUNCTION blendFunc;

public:
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ȭ�鿡 ���
	void Render(HDC hdc, int destX = 0, int destY = 0, bool isCenterRenderring = FALSE);
	// �����̴� �̹��� ���
	void FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY);
	// ������� �̹��� ���
	void AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring);
	
	//(�̱���)������ũ : �̹����� Ű���ٰ� ���� �ػ󵵷� �����ϸ鼭 �ػ� ������ ������� ����
	void MosaicRender(HDC hdc, int destX, int destY, bool isCenterRenderring = false);
	//(�̱���)�� : ���� ������ �����ؼ� ����� ������ ���� ������ ��µǵ��� ����
	void BlurRender(HDC hdc, int destX, int destY, bool isCenterRenderring = false);



	void Release();

	// get, set
	HDC GetMemDC()
	{
		if (this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	}
	
	// �� ���־��ʿ��� ������� ȣ��
	BLENDFUNCTION* GetBlendFunc() { return &(this->blendFunc); }
};
