#include "Image.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::EMPTY;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = FALSE;
    this->transColor = FALSE;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height,
    bool isTransparent/* = FALSE*/, COLORREF transColor/* = FALSE*/)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap =
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::FILE;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    //���� ���� ������
    this->blendFunc.AlphaFormat = 0;
    this->blendFunc.BlendFlags = 0;
    this->blendFunc.BlendOp = AC_SRC_OVER;
    this->blendFunc.SourceConstantAlpha = 255;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap =
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::FILE;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;
}

void Image::Render(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;

    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(hdc,x, y,imageInfo->width, imageInfo->height,
            imageInfo->hMemDC,0, 0,imageInfo->width, imageInfo->height,transColor);
    }
    else
    {
        // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
        BitBlt(
            hdc,                // ���� ������ DC
            destX, destY,       // ���� ���� ��ġ
            imageInfo->width,   // �������� ����� ����ũ��
            imageInfo->height,  // �������� ����� ����ũ��
            imageInfo->hMemDC,  // ���� DC
            0, 0,               // �������� ���� ���� ��ġ
            SRCCOPY             // ���� �ɼ�
        );
    }


}

void Image::FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY)
{
    imageInfo->currFrameX = currFrameX;
    imageInfo->currFrameY = currFrameY;

    int x = destX - (imageInfo->frameWidth / 2);
    int y = destY - (imageInfo->frameHeight / 2);

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,                // ������ DC
            x, y,               // ���� ��ġ
            imageInfo->frameWidth, imageInfo->frameHeight,  // ���� ũ��

            imageInfo->hMemDC,  // ���� DC
            imageInfo->frameWidth * imageInfo->currFrameX,  // ���� X ��ġ
            imageInfo->frameHeight * imageInfo->currFrameY, // ���� Y ��ġ
            imageInfo->frameWidth, imageInfo->frameHeight,  // ���� ũ��
            transColor  // ������ ����
        );
    }
    else
    {
        BitBlt(
            hdc,
            x, y,
            imageInfo->frameWidth,
            imageInfo->frameHeight,
            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            SRCCOPY
        );
    }
}

void Image::AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    // 1. ������ DC�� �׷��� �ִ� ������ BlendDC�� ����
    BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, hdc, x, y, SRCCOPY);
    // 2. ����� �̹��� DC�� ������ BlendDC �� ������ ������ �����ϸ鼭 ����
    GdiTransparentBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, RGB(255, 0, 255));

    // 3. 
    AlphaBlend(hdc, x, y, imageInfo->width, imageInfo->height,
        imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);

    /*  
    if (image)
    {
        BLENDFUNCTION* blendFunc = image->GetBlendFunc();

        if (blendFunc->SourceConstantAlpha > 0)
        {
            blendFunc->SourceConstantAlpha--;
        }
    }
    */
}


//(�̱���)������ũ : �̹����� Ű���ٰ� ���� �ػ󵵷� �����ϸ鼭 �ػ� ������ ������� ����
void Image::MosaicRender(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    // 1. �̹����� ũ�� ȣ��
    BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, hdc, x, y, SRCCOPY);
    // 2. ����� �̹��� DC�� ������ BlendDC �� ���� �ػ󵵷� ������ ������ �����ϸ鼭 ����
    GdiTransparentBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, RGB(255, 0, 255));

    // 3. 
    AlphaBlend(hdc, x, y, imageInfo->width, imageInfo->height,
        imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);

    /* ����
    if (isTransparent)
    {

        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
        BitBlt(
            hdc,                // ���� ������ DC
            x, y,               // ���� ���� ��ġ
            imageInfo->width,   // �������� ����� ����ũ��
            imageInfo->height,  // �������� ����� ����ũ��
            imageInfo->hMemDC,  // ���� DC
            0, 0,               // �������� ���� ���� ��ġ
            SRCCOPY             // ���� �ɼ�
        );
    }
    */


}
//(�̱���)�� : ���� ������ �����ؼ� ����� ������ ���� ������ ��µǵ��� ���� - ������
void Image::BlurRender(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    /* ����
    if (isTransparent)
    {

        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
        BitBlt(
            hdc,                // ���� ������ DC
            x, y,               // ���� ���� ��ġ
            imageInfo->width,   // �������� ����� ����ũ��
            imageInfo->height,  // �������� ����� ����ũ��
            imageInfo->hMemDC,  // ���� DC
            0, 0,               // �������� ���� ���� ��ġ
            SRCCOPY             // ���� �ɼ�
        );
    }
    */


}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        if (imageInfo->hBlendDC != NULL)
        {
            SelectObject(imageInfo->hBlendDC, imageInfo->hBlendOldBit);
            DeleteObject(imageInfo->hBlendBit);
            DeleteDC(imageInfo->hBlendDC);
        }

        delete imageInfo;
        imageInfo = nullptr;
    }
}
