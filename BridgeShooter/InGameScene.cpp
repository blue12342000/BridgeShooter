#include "InGameScene.h"
#include "Image.h"
#include "SpaceShip.h"
#include "Planet_SSJ.h"
#include "Planet04.h"
#include "JinHwang.h"
#include "Planet_KMS.h"
#include "Item.h"
#include "Missile.h"
#include "HPgauge.h"
#include "GameScene.h"
#include "SpaceShip_Red.h"
#include "SpaceShip_Gray.h"

HRESULT InGameScene::Init()
{
    
    switch (DataManager::GetSingleton()->GetSelectedCharacter())
    {
    case (int)DataManager::CHARACTER_CODE::YELLOW:
        lpPlayer = new SpaceShip();
        lpPlayer->Init();
        lpPlayer->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT });
        break;
    case (int)DataManager::CHARACTER_CODE::RED:
        lpPlayer = new SpaceShip();
        lpPlayer->Init();
        lpPlayer->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT });
        break;
    case (int)DataManager::CHARACTER_CODE::GRAY:
        lpPlayer = new SpaceShip_Gray();
        lpPlayer->Init();
        lpPlayer->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT });
        break;
    }
    
   
    lpPlanet04 = new Planet04();
    lpPlanet04->Init();
    lpPlanet04->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT/4 });

    lpPlanetSSJ = new Planet_SSJ();
    lpPlanetSSJ->Init();
    lpPlanetSSJ->SetPos({(float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    lpPlanetKMS = new Planet_KMS();
    lpPlanetKMS->Init();
    lpPlanetKMS->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    lpItem = new Item();
    lpItem->Init();
    lpItem->SetPos({ (float)WINSIZE_WIDTH /8, (float)WINSIZE_HEIGHT /7  });

    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");
    lpBackImage2 = ImageManager::GetSingleton()->FindImage("SPACE");

    frame = 0;
    elapsedTime = 0;
        
    backgroundMover = 0;
    isEnemyHitPlayer = false;
    isPlayerHitEnemy = false;

    lpJinHwang = new JinHwang();
    lpJinHwang->Init();
    lpJinHwang->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    lpHpGauge = new HpGauge();
    lpHpGauge->Init();
    lpHpGauge->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 20 });
     return S_OK;
}

void InGameScene::Release()
{
    if (lpPlayer)
    {
        lpPlayer->Release();
        delete lpPlayer;
        lpPlayer = nullptr;
    }

    if (lpPlanetSSJ)
    {
        lpPlanetSSJ->Release();
        delete lpPlanetSSJ;
        lpPlanetSSJ = nullptr;
    }

    if (lpPlanet04)
    {
        lpPlanet04->Release();
        delete lpPlanet04;
        lpPlanet04 = nullptr;
    }
    if (lpPlanetKMS)
    {
        lpPlanetKMS->Release();
        delete lpPlanetKMS;
        lpPlanetKMS = nullptr;
    }

    if (lpJinHwang)
    {
        lpJinHwang->Release();
        delete lpJinHwang;
        lpJinHwang = nullptr;
    }

    if (lpItem)
    {
        lpItem->Release();
        delete lpItem;
        lpItem = nullptr;
    }

    if (lpHpGauge)
    {
        lpHpGauge->Release();
        delete lpHpGauge;
        lpHpGauge = nullptr;
    }
}

void InGameScene::Update(float deltaTime)
{
    if (KeyManager::GetSingleton()->IsKeyDownOne('M'))
    {
        isOnlyPlayer = !isOnlyPlayer;
    }
    if (KeyManager::GetSingleton()->IsKeyDownOne(VK_ESCAPE))
    {
        SceneManager::GetSingleton()->ChangeScene();
    }

    if (KeyManager::GetSingleton()->IsKeyDownOne('N'))
    {
        EffectManager::GetSingleton()->Explosion(lpPlanetSSJ->pos, ImageManager::GetSingleton()->FindImage("JINHWANG"), 0, 10, 20, 20);
    }

    CheckCollision();

    if (lpPlayer) lpPlayer->Update(deltaTime);

    //if (lpPlanet04) lpPlanet04->Update(deltaTime);
    //if (!isOnlyPlayer && lpPlanetSSJ) lpPlanetSSJ->Update(deltaTime);
    if (lpPlanetSSJ) lpPlanetSSJ->Update(deltaTime);
    //if (lpJinHwang) lpJinHwang->Update(deltaTime);
    //if (lpPlanetKMS) lpPlanetKMS->Update(deltaTime);

    if (lpItem) lpItem->Update(deltaTime);
    if (lpHpGauge) lpHpGauge->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime);
    
    EffectManager::GetSingleton()->Update(deltaTime);

    backgroundMover += 300 *deltaTime;
    if (backgroundMover >= 800) backgroundMover = 0;


}

void InGameScene::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();

    if (lpBackImage) lpBackImage->Render(hBackDC, 0, backgroundMover);
    if (lpBackImage2) lpBackImage2->Render(hBackDC, 0, -800+backgroundMover);

    if (lpPlayer) lpPlayer->Render(hBackDC);

    //if (lpPlanet04) lpPlanet04->Render(hBackDC);
    if (lpPlanetSSJ) lpPlanetSSJ->Render(hBackDC);
    //if (lpJinHwang) lpJinHwang->Render(hBackDC);
    //if (lpPlanetKMS) lpPlanetKMS->Render(hBackDC);

    if (lpItem) lpItem->Render(hBackDC);

    if (lpHpGauge) lpHpGauge->Render(hBackDC);
    EffectManager::GetSingleton()->Render(hBackDC);
    MissileManager::GetSingleton()->Render(hBackDC);
    
    //if (isEnemyHitPlayer)
    //    lpJinHwang->Render(hBackDC);
    //if(isPlayerHitEnemy)
    //    lpPlanetKMS->Render(hBackDC);


    lpBackBuffer->Render(hdc);
   
}

void InGameScene::CheckCollision()
{
    isEnemyHitPlayer = false;
    isPlayerHitEnemy = false;
    vector<Missile*>& vLpEnemyMissile = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::ENEMY);
    vector<Missile*>& vLpPlayerMissile = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::PLAYER);
    
    float distance = 100.0f;
    float dX = 0;
    float dY = 0;

    for (int i = 0; i < vLpEnemyMissile.size();)
    {
        dX = vLpEnemyMissile[i]->pos.x + vLpEnemyMissile[i]->deltaMove.deltaPos.x - lpPlayer->pos.x;
        dY = vLpEnemyMissile[i]->pos.y + vLpEnemyMissile[i]->deltaMove.deltaPos.y - lpPlayer->pos.y;
        distance = sqrt(dX * dX + dY * dY);

        if (distance <= vLpEnemyMissile[i]->collider.width / 2 + lpPlayer->collider.width / 2)
        {
            EffectManager::GetSingleton()->PlayImage({ vLpEnemyMissile[i]->pos.x + vLpEnemyMissile[i]->deltaMove.deltaPos.x , vLpEnemyMissile[i]->pos.y + vLpEnemyMissile[i]->deltaMove.deltaPos.y }, "EFFECT_01", 10);
            MissileManager::GetSingleton()->DisableMissile(UNIT_KIND::ENEMY, i);
            isEnemyHitPlayer = true;
            lpHpGauge->SetPlayerMaxHp(lpHpGauge->GetPlayerMaxHp() - 1);
        }
        else
        {
            ++i;
        }
    }

    float distance2 = 100.0f;
    float dX2 = 0;
    float dY2 = 0;

    for (int i = 0; i < vLpPlayerMissile.size();)
    {
        dX2 = vLpPlayerMissile[i]->pos.x + vLpPlayerMissile[i]->deltaMove.deltaPos.x - lpPlanetSSJ->pos.x;
        dY2 = vLpPlayerMissile[i]->pos.y + vLpPlayerMissile[i]->deltaMove.deltaPos.y - lpPlanetSSJ->pos.y;
        distance2 = sqrt(dX2 * dX2 + dY2 * dY2);
        if (distance2 <= vLpPlayerMissile[i]->collider.width / 2 + lpPlanetSSJ->collider.width / 2)
        {
            EffectManager::GetSingleton()->PlayImage({ vLpPlayerMissile[i]->pos.x + vLpPlayerMissile[i]->deltaMove.deltaPos.x , vLpPlayerMissile[i]->pos.y + vLpPlayerMissile[i]->deltaMove.deltaPos.y }, "EFFECT_01", 10);
            MissileManager::GetSingleton()->DisableMissile(UNIT_KIND::PLAYER, i);
            isPlayerHitEnemy = true;
            lpHpGauge->SetbossMaxHp(lpHpGauge->GetbossMaxHp() - 1);
        }
        else
        {
            ++i;
        }
    }



}
