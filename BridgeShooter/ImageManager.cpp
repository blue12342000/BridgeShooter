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

    mLpImageDatas.insert(make_pair("MISSILE_03", new Image()));
    mLpImageDatas["MISSILE_03"]->RotateInit("Image/Missile/Missile_03.bmp", 14, 17, 1, 1, 1, 36);

    mLpImageDatas.insert(make_pair("MISSILE_04", new Image()));
    mLpImageDatas["MISSILE_04"]->RotateInit("Image/Missile/Missile_04.bmp", 47 / 2, 47 / 2, 1, 1, 1, 36);

    mLpImageDatas.insert(make_pair("MISSILE_05", new Image()));
    mLpImageDatas["MISSILE_05"]->RotateInit("Image/Missile/Missile_05.bmp", 45 / 2, 45 / 2, 1, 1, 1, 36);

    mLpImageDatas.insert(make_pair("MISSILE_06", new Image()));
    mLpImageDatas["MISSILE_06"]->RotateInit("Image/Missile/Missile_06.bmp", 132 / 2, 33 / 2, 4, 1, 4, 36);

    mLpImageDatas.insert(make_pair("MISSILE_07", new Image()));
    mLpImageDatas["MISSILE_07"]->RotateInit("Image/Missile/Missile_07.bmp", 144 / 2, 36 / 2, 4, 1, 4, 36);

    mLpImageDatas.insert(make_pair("MISSILE_08", new Image()));
    mLpImageDatas["MISSILE_08"]->RotateInit("Image/Missile/Missile_08.bmp", 144 / 2, 36 / 2, 4, 1, 4, 36);

    mLpImageDatas.insert(make_pair("MISSILE_09", new Image()));
    mLpImageDatas["MISSILE_09"]->RotateInit("Image/Missile/Missile_09.bmp", 156 / 2, 39 / 2, 4, 1, 4, 36);

    mLpImageDatas.insert(make_pair("MISSILE_10", new Image()));
    mLpImageDatas["MISSILE_10"]->RotateInit("Image/Missile/Missile_10.bmp", 144 / 2, 48 / 2, 2, 1, 2, 36);

    mLpImageDatas.insert(make_pair("PLANET_SSJ", new Image()));
    mLpImageDatas["PLANET_SSJ"]->Init("Image/Unit/Planet/Planet_SSJ.bmp", 20000, 266, 50, 1, 50, true, RGB(255, 0, 255));

    mLpImageDatas.insert(make_pair("Planet04", new Image()));
    mLpImageDatas["Planet04"]->Init("Image/Unit/Planet/Planet_04_square2.bmp", 2800, 3840, 10, 12, 120, true);

    mLpImageDatas.insert(make_pair("Planet_KMS", new Image()));
    mLpImageDatas["Planet_KMS"]->Init("Image/Unit/Planet/planet_KMS.bmp", 134 * 10, 134, 10, 1, 10, true, RGB(0, 0, 0));

    mLpImageDatas.insert(make_pair("Item_Power", new Image()));
    mLpImageDatas["Item_Power"]->Init("Image/Item/Item_Power.bmp", 504, 84, 6, 1, 6, true);

    mLpImageDatas.insert(make_pair("Item_Bomb", new Image()));
    mLpImageDatas["Item_Bomb"]->Init("Image/Item/Item_Bomb.bmp", 504, 84, 6, 1, 4, true);

    mLpImageDatas.insert(make_pair("Item_Speed", new Image()));
    mLpImageDatas["Item_Speed"]->Init("Image/Item/Item_Speed.bmp", 504, 84, 6, 1, 6, true);

    mLpImageDatas.insert(make_pair("Item_Health", new Image()));
    mLpImageDatas["Item_Health"]->Init("Image/Item/Item_Health.bmp", 504, 84, 6, 1, 4, true);

    mLpImageDatas.insert(make_pair("BossHpGauge", new Image()));
    mLpImageDatas["BossHpGauge"]->Init("Image/UI/BossHpGauge.bmp", 600, 76, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("HpGauge_Default", new Image()));
    mLpImageDatas["HpGauge_Default"]->Init("Image/UI/HpGauge.bmp", 1010, 76, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("HpGauge_Blank", new Image()));
    mLpImageDatas["HpGauge_Blank"]->Init("Image/UI/HpGauge2.bmp", 1010, 76, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("HpGauge_In", new Image()));
    mLpImageDatas["HpGauge_In"]->Init("Image/UI/HpGauge3.bmp", 1010, 76, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("TITLE", new Image()));
    mLpImageDatas["TITLE"]->Init("Image/UI/Title.bmp", WINSIZE_WIDTH, WINSIZE_HEIGHT, true);

    mLpImageDatas.insert(make_pair("TITLE_PRESSKEY", new Image()));
    mLpImageDatas["TITLE_PRESSKEY"]->Init("Image/UI/Title_presskey.bmp", 600, 800, true);

    mLpImageDatas.insert(make_pair("EFFECT_01", new Image()));
    mLpImageDatas["EFFECT_01"]->Init("Image/Effect/Effect_01.bmp", 108, 36, 3, 1, 3, true);
    
    mLpImageDatas.insert(make_pair("SELECT_YELLOW", new Image()));
    mLpImageDatas["SELECT_YELLOW"]->Init("Image/UI/Select_Yellow.bmp", 200, 200, true);

    mLpImageDatas.insert(make_pair("SELECT_RED", new Image()));
    mLpImageDatas["SELECT_RED"]->Init("Image/UI/Select_Red.bmp", 200, 200, true);

    mLpImageDatas.insert(make_pair("SELECT_GRAY", new Image()));
    mLpImageDatas["SELECT_GRAY"]->Init("Image/UI/Select_Gray.bmp", 200, 200, true);

    mLpImageDatas.insert(make_pair("Enemy_1", new Image()));
    mLpImageDatas["Enemy_1"]->Init("Image/Unit/Mob/mob1_sprite.bmp", 50 * 4, 50, 4, 1, 4, true);

    mLpImageDatas.insert(make_pair("Enemy_2", new Image()));
    mLpImageDatas["Enemy_2"]->Init("Image/Unit/Mob/mob2_sprite.bmp", 50 * 4, 50, 4, 1, 4, true);

    mLpImageDatas.insert(make_pair("Enemy_3", new Image()));
    mLpImageDatas["Enemy_3"]->Init("Image/Unit/Mob/mob3_sprite.bmp", 50 * 4, 50, 4, 1, 4, true);

    mLpImageDatas.insert(make_pair("Enemy_4", new Image()));
    mLpImageDatas["Enemy_4"]->Init("Image/Unit/Mob/mob4_sprite.bmp", 50 * 4, 50, 4, 1, 4, true);
    //이하 테스트용 더미 이미지
    mLpImageDatas.insert(make_pair("LifeMiniYELLOW", new Image()));
    mLpImageDatas["LifeMiniYELLOW"]->Init("Image/UI/Select_Yellow.bmp", 200/3, 200/3, true);

    mLpImageDatas.insert(make_pair("LifeMiniRED", new Image()));
    mLpImageDatas["LifeMiniRED"]->Init("Image/UI/Select_Red.bmp", 200/3, 200 / 3, true);

    mLpImageDatas.insert(make_pair("LifeMiniGRAY", new Image()));
    mLpImageDatas["LifeMiniGRAY"]->Init("Image/UI/Select_Gray.bmp", 200 / 3, 200 / 3, true);
    
    mLpImageDatas.insert(make_pair("NowMissile_1", new Image()));
    mLpImageDatas["NowMissile_1"]->Init("Image/UI/NowMissile_1.bmp", 700/4, 291 / 4, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("NowMissile_2", new Image()));
    mLpImageDatas["NowMissile_2"]->Init("Image/UI/NowMissile_2.bmp", 700 / 4, 291 / 4, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("NowMissile_3", new Image()));
    mLpImageDatas["NowMissile_3"]->Init("Image/UI/NowMissile_3.bmp", 700 / 4, 291 / 4, 1, 1, 1, true);
    
    mLpImageDatas.insert(make_pair("NowMissile_4", new Image()));
    mLpImageDatas["NowMissile_4"]->Init("Image/UI/NowMissile_4.bmp", 700 / 4, 291 / 4, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("NowMissile_MAXXX", new Image()));
    mLpImageDatas["NowMissile_MAXXX"]->Init("Image/UI/NowMissile_MAXXX.bmp", 700 / 4, 291 / 4, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("NowMissile_LVMAXXX", new Image()));
    mLpImageDatas["NowMissile_LVMAXXX"]->Init("Image/UI/NowMissile_LVMAXXX.bmp", 700 /4, 291/4, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("Manual", new Image()));
    mLpImageDatas["Manual"]->Init("Image/UI/Manual.bmp", 700/4, 586/4, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("MOVING_CAT", new Image()));
    mLpImageDatas["MOVING_CAT"]->Init("Image/UI/MovingCat.bmp", 1456/2, 209/2, 8, 1, 8, true);

    mLpImageDatas.insert(make_pair("LOADING_CAT", new Image()));
    mLpImageDatas["LOADING_CAT"]->Init("Image/UI/LoadingCat.bmp", 1004, 251, 4, 1, 4, true);

    mLpImageDatas.insert(make_pair("SPACESHIP_RED", new Image()));
    mLpImageDatas["SPACESHIP_RED"]->Init("Image/Unit/SpaceShip/SpaceShip_Red.bmp", 507/2, 218/2, 3, 1, 3, true, RGB(255,5,255));

    mLpImageDatas.insert(make_pair("SPACESHIP_GRAY", new Image()));
    mLpImageDatas["SPACESHIP_GRAY"]->Init("Image/Unit/SpaceShip/SpaceShip_Gray.bmp", 512/2, 217/2, 4, 1, 4, true);

    mLpImageDatas.insert(make_pair("SELECT_INFO", new Image()));
    mLpImageDatas["SELECT_INFO"]->Init("Image/UI/SelectInfo.bmp", WINSIZE_WIDTH, WINSIZE_HEIGHT, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("ENDING", new Image()));
    mLpImageDatas["ENDING"]->Init("Image/UI/Ending.bmp", WINSIZE_WIDTH, WINSIZE_HEIGHT, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("hp_01", new Image()));
    mLpImageDatas["hp_01"]->Init("Image/UI/hp_01.bmp", 24, 12, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("hp_02", new Image()));
    mLpImageDatas["hp_02"]->Init("Image/UI/hp_02.bmp", 24, 12, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("hp_03", new Image()));
    mLpImageDatas["hp_03"]->Init("Image/UI/hp_03.bmp", 24, 12, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("hp_04", new Image()));
    mLpImageDatas["hp_04"]->Init("Image/UI/hp_04.bmp", 24, 12, 1, 1, 1, true);

    mLpImageDatas.insert(make_pair("Ghoust", new Image()));
    mLpImageDatas["Ghoust"]->Init("Image/UI/Ghoust.bmp", 800, 320, 2, 1, 2, true);

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
