#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
    mLpImageDatas.insert(make_pair("BACKBUFFER", new Image()));
    mLpImageDatas["BACKBUFFER"]->Init(WINSIZE_WIDTH, WINSIZE_HEIGHT);

    mLpImageDatas.insert(make_pair("SPACE", new Image()));
    mLpImageDatas["SPACE"]->Init("Image/UI/Space.bmp", WINSIZE_WIDTH, WINSIZE_HEIGHT, 1, 1, 1);

    mLpImageDatas.insert(make_pair("SPACESHIP_IDLE", new Image()));
    mLpImageDatas["SPACESHIP_IDLE"]->Init("Image/Unit/SpaceShip/SpaceShip_IDLE.bmp", 640 / 2, 280 / 2, 4, 1, 4, true);

    mLpImageDatas.insert(make_pair("SPACESHIP_LEFT", new Image()));
    mLpImageDatas["SPACESHIP_LEFT"]->Init("Image/Unit/SpaceShip/SpaceShip_LEFT.bmp", 640 / 2, 280 / 2, 4, 1, 4, true);

    mLpImageDatas.insert(make_pair("SPACESHIP_RIGHT", new Image()));
    mLpImageDatas["SPACESHIP_RIGHT"]->Reverse(*mLpImageDatas["SPACESHIP_LEFT"]);

    mLpImageDatas.insert(make_pair("JINHWANG", new Image()));
    mLpImageDatas["JINHWANG"]->Init("Image/Unit/JinHwang/JinHwang.bmp", 5000 / 2, 2754 / 2, 10, 9, 90, true);

    mLpImageDatas.insert(make_pair("MISSILE_01", new Image()));
    mLpImageDatas["MISSILE_01"]->RotateInit("Image/Missile/Missile_01.bmp", 58 / 2, 58 / 2, 1, 1, 1, 36);

    mLpImageDatas.insert(make_pair("MISSILE_02", new Image()));
    mLpImageDatas["MISSILE_02"]->RotateInit("Image/Missile/Missile_02.bmp", 40 / 2, 40 / 2, 1, 1, 1, 36);

    mLpImageDatas.insert(make_pair("PLANET_SSJ", new Image()));
    mLpImageDatas["PLANET_SSJ"]->Init("Image/Unit/Planet/Planet_SSJ.bmp", 20000, 266, 50, 1, 50, true, RGB(255, 0, 255));
 
    mLpImageDatas.insert(make_pair("Planet04", new Image()));
    mLpImageDatas["Planet04"]->Init("Image/Unit/Planet/Planet_04_square2.bmp", 2800 , 3840, 10, 12, 120, true);

    mLpImageDatas.insert(make_pair("Planet_KMS", new Image()));
    mLpImageDatas["Planet_KMS"]->Init("Image/Unit/Planet/planet_KMS.bmp", 134*10,134, 10, 1, 10, true, RGB(0, 0, 0));
    return S_OK;
}

void ImageManager::Release()
{
    for (auto it = mLpImageDatas.begin(); it != mLpImageDatas.end(); ++it)
    {
        if ((it->second))
        {
            (it->second)->Release();
            delete (it->second);
            (it->second) = nullptr;
        }
    }
    mLpImageDatas.clear();
}

Image* ImageManager::FindImage(string key)
{
    if (mLpImageDatas.find(key) == mLpImageDatas.end())
    {
        return nullptr;
    }

    return mLpImageDatas[key];
}
