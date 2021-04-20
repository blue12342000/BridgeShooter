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
#include "PlayerController.h"
#include "JinHwangAIContoller.h"
#include "SpaceShip_Red.h"
#include "SpaceShip_Gray.h"
#include "EnemyGroup.h"
#include "SSJAIController.h"

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
        lpPlayer = new SpaceShip_Red();
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

    lpMob1 = new EnemyGroup();
    lpMob1->Init();

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
    isPlayerHitItem = false;
    isItemAlive = false;

    lpJinHwang = new JinHwang();
    lpJinHwang->Init();
    lpJinHwang->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    lpHpGauge = new HpGauge();
    lpHpGauge->Init();
 
    lpPlayerController = new PlayerController();
    lpPlayerController->Init();
    lpPlayerController->SetController(lpPlayer);

    //lpEnemyController = new JinHwangAIContoller();
    //lpEnemyController->Init();
    //lpEnemyController->SetController(lpJinHwang);

    lpEnemyController = new SSJAIController();
    lpEnemyController->Init();
    lpEnemyController->SetController(lpPlanetSSJ);

     return S_OK;
}

void InGameScene::Release()
{
    MissileManager::GetSingleton()->Release();

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
    /*if (lpMob1)
    {
        lpMob1->Release();
        delete lpMob1;
        lpMob1 = nullptr;
    }*/
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

    if (lpPlayerController)
    {
        lpPlayerController->Release();
        delete lpPlayerController;
        lpPlayerController = nullptr;
    }
}

void InGameScene::Update(float deltaTime)
{
    if (KeyManager::GetSingleton()->IsKeyDownOne('M'))
    {
        isOnlyPlayer = !isOnlyPlayer;
    }

    if (KeyManager::GetSingleton()->IsKeyDownOne('N'))
    {
        EffectManager::GetSingleton()->Explosion(lpPlanetSSJ->pos, ImageManager::GetSingleton()->FindImage("Enemy_2"), 0, 80, 5, 5);
    }

    CheckCollision();

    if (lpPlayerController) lpPlayerController->Update(deltaTime);
    if (lpEnemyController) lpEnemyController->Update(deltaTime);

    //if (lpPlanet04) lpPlanet04->Update(deltaTime);
    //if (!isOnlyPlayer && lpPlanetSSJ) lpPlanetSSJ->Update(deltaTime);
    //if (lpPlanetSSJ) lpPlanetSSJ->Update(deltaTime);
    //if (lpJinHwang) lpJinHwang->Update(deltaTime);
    //if (lpPlanetKMS) lpPlanetKMS->Update(deltaTime);
    //if (lpMob1) lpMob1->Update(deltaTime);

    if (lpItem) lpItem->Update(deltaTime);
    if (lpHpGauge) lpHpGauge->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime);
    
    EffectManager::GetSingleton()->Update(deltaTime);

    backgroundMover += 300 *deltaTime;
    if (backgroundMover >= 800) backgroundMover = 0;

    if (KeyManager::GetSingleton()->IsKeyDownOne(VK_ESCAPE))
    {
        SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::TITLE);
    }
}

void InGameScene::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();

    if (lpBackImage) lpBackImage->Render(hBackDC, 0, backgroundMover);
    if (lpBackImage2) lpBackImage2->Render(hBackDC, 0, -800+backgroundMover);

    if (lpPlayerController) lpPlayerController->Render(hBackDC);
    if (lpEnemyController) lpEnemyController->Render(hBackDC);

    //if (lpPlanet04) lpPlanet04->Render(hBackDC);
    //if (lpPlanetSSJ) lpPlanetSSJ->Render(hBackDC);
    //if (lpJinHwang) lpJinHwang->Render(hBackDC);
    //if (lpPlanetKMS) lpPlanetKMS->Render(hBackDC);
    //if (lpMob1)lpMob1->Render(hBackDC);

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
    isPlayerHitItem = false;
    vector<Missile*>& vLpEnemyMissile = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::ENEMY);
    vector<Missile*>& vLpPlayerMissile = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::PLAYER);
    //플레이어의 체력과 행성의 체력을 가져온다.

    float distance = 100.0f;
    float dX = 0;
    float dY = 0;

    //적이 나를 떄릴때
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
            lpHpGauge->SetPlayerMaxHp(lpHpGauge->GetPlayerMaxHp() - 10);
        }
        else
        {
            ++i;
        }
    }

    float distance2 = 100.0f;
    float dX2 = 0;
    float dY2 = 0;

    //내가 적을 때릴때
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
            lpHpGauge->SetbossMaxHp(lpHpGauge->GetbossMaxHp() - 10);
        }
        else
        {
            ++i;
        }
    }

    float distance3 = 100.0f;
    float dX3 = 0;
    float dY3 = 0;

    dX3 = lpPlayer->pos.x - lpItem->pos.x;
    dY3 = lpPlayer->pos.y - lpItem->pos.y;
    distance3 = sqrt(dX3 * dX3 + dY3 * dY3);
    if (distance3 <= lpItem->collider.width / 2 + lpPlayer->collider.width / 2)
    {
        EffectManager::GetSingleton()->PlayImage({ lpPlayer->pos.x , lpPlayer->pos.y }, "EFFECT_01", 10);
        //lpItem->Release();   isItemdisabled = true;
        //아이템 충돌판정 및 활동 중지
        //isPlayerHitItem = true;
    }

}