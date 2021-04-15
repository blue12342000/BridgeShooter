#include "Image.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    lpImageInfo = new ImageInfo();
    lpImageInfo->resID = 0;
    lpImageInfo->hMemDC = CreateCompatibleDC(hdc);
    lpImageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    lpImageInfo->width = width;
    lpImageInfo->height = height;
    lpImageInfo->loadType = IMAGE_LOAD_TYPE::EMPTY;

    lpImageInfo->maxFrameX = 1;
    lpImageInfo->maxFrameY = 1;
    lpImageInfo->totalFrame = 1;

    DeleteObject(SelectObject(lpImageInfo->hMemDC, lpImageInfo->hBitmap));
    ReleaseDC(g_hWnd, hdc);

    if (lpImageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    lpImageInfo->isTransparent = false;
    lpImageInfo->transColor = 0;

    lpBlendInfo = nullptr;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    lpImageInfo = new ImageInfo();
    lpImageInfo->resID = 0;
    lpImageInfo->hMemDC = CreateCompatibleDC(hdc);
    lpImageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    lpImageInfo->width = width;
    lpImageInfo->height = height;
    lpImageInfo->loadType = IMAGE_LOAD_TYPE::FILE;

    lpImageInfo->maxFrameX = 1;
    lpImageInfo->maxFrameY = 1;
    lpImageInfo->totalFrame = 1;

    DeleteObject(SelectObject(lpImageInfo->hMemDC, lpImageInfo->hBitmap));
    ReleaseDC(g_hWnd, hdc);

    if (lpImageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    lpImageInfo->isTransparent = isTransparent;
    lpImageInfo->transColor = transColor;

    lpBlendInfo = new BlendInfo();
    lpBlendInfo->blendFunc.AlphaFormat = 0;
    lpBlendInfo->blendFunc.BlendFlags = 0;
    lpBlendInfo->blendFunc.BlendOp = AC_SRC_OVER;
    lpBlendInfo->blendFunc.SourceConstantAlpha = 255;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, int totalFrame, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    lpImageInfo = new ImageInfo();
    lpImageInfo->resID = 0;
    lpImageInfo->hMemDC = CreateCompatibleDC(hdc);
    lpImageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    lpImageInfo->width = width / maxFrameX;
    lpImageInfo->height = height / maxFrameY;
    lpImageInfo->loadType = IMAGE_LOAD_TYPE::FILE;

    lpImageInfo->maxFrameX = maxFrameX;
    lpImageInfo->maxFrameY = maxFrameY;
    lpImageInfo->totalFrame = totalFrame;

    DeleteObject(SelectObject(lpImageInfo->hMemDC, lpImageInfo->hBitmap));
    ReleaseDC(g_hWnd, hdc);

    if (lpImageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    lpImageInfo->isTransparent = isTransparent;
    lpImageInfo->transColor = transColor;

    lpBlendInfo = new BlendInfo();
    lpBlendInfo->blendFunc.AlphaFormat = 0;
    lpBlendInfo->blendFunc.BlendFlags = 0;
    lpBlendInfo->blendFunc.BlendOp = AC_SRC_OVER;
    lpBlendInfo->blendFunc.SourceConstantAlpha = 255;

    return S_OK;
}

void Image::Render(HDC hdc, int destX, int destY, int frame)
{
    if (lpImageInfo->isTransparent)
    {
        GdiTransparentBlt(hdc, destX, destY,lpImageInfo->width, lpImageInfo->height,
            lpImageInfo->hMemDC,0, 0,lpImageInfo->width, lpImageInfo->height, lpImageInfo->transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY, lpImageInfo->width, lpImageInfo->height, lpImageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void Image::AlphaRender(HDC hdc, int destX, int destY)
{
    BitBlt(lpBlendInfo->hBlendDC, 0, 0, lpImageInfo->width, lpImageInfo->height, hdc, destX, destY, SRCCOPY);

    GdiTransparentBlt(lpBlendInfo->hBlendDC, 0, 0, lpImageInfo->width, lpImageInfo->height,
        lpImageInfo->hMemDC, 0, 0, lpImageInfo->width, lpImageInfo->height, lpImageInfo->transColor);

    AlphaBlend(hdc, destX, destY, lpImageInfo->width, lpImageInfo->height,
        lpBlendInfo->hBlendDC, 0, 0, lpImageInfo->width, lpImageInfo->height, lpBlendInfo->blendFunc);
}

void Image::Release()
{
    if (lpImageInfo)
    {
        DeleteObject(lpImageInfo->hBitmap);
        DeleteDC(lpImageInfo->hMemDC);
        delete lpImageInfo;
        lpImageInfo = nullptr;

        if (lpBlendInfo)
        {
            DeleteObject(lpBlendInfo->hBlendBit);
            DeleteDC(lpBlendInfo->hBlendDC);
            delete lpBlendInfo;
            lpBlendInfo = nullptr;
        }
    }
}
