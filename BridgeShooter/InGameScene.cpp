#include "InGameScene.h"
#include "Image.h"
#include "SpaceShip.h"
#include "Planet_SSJ.h"
#include "Planet04.h"
#include "JinHwang.h"
#include "Planet_KMS.h"
#include "Item.h"
#include "Missile.h"
#include "UIobject.h"
#include "GameScene.h"
#include "PlayerController.h"
#include "JinHwangAIContoller.h"
#include "Planet04AIController.h"
#include "SpaceShip_Red.h"
#include "SpaceShip_Gray.h"
#include "AlienBlue.h"
#include "AlienGreen.h"
#include "AlienRed.h"
#include "AlienYellow.h"
#include "AlienAIController.h"
#include "KmsAIController.h"
#include "SSJAIController.h"
#include "Animation.h"

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
    lpPlanetSSJ->SetPos({(float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 - 300 });

    lpPlanetKMS = new Planet_KMS();
    lpPlanetKMS->Init();
    lpPlanetKMS->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    lpJinHwang = new JinHwang();
    lpJinHwang->Init();
    lpJinHwang->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    vEnemys.push_back(new AlienBlue());
    vEnemys.push_back(new AlienGreen());
    vEnemys.push_back(new AlienRed());
    vEnemys.push_back(new AlienYellow());

    //for (int i = 0; i < vEnemys.size();i++)
    //{
    //    vEnemys[i]->Init();
    //}

    lpItem = new Item();
    lpItem->Init();
    lpItem->SetPos({ (float)WINSIZE_WIDTH /8, (float)WINSIZE_HEIGHT /7  });

    vLpEnemyController.push_back(new JinHwangAIContoller()); 
    vLpEnemyController.push_back(new SSJAIController());
    vLpEnemyController.push_back(new Planet04AIcontroller());
    vLpEnemyController.push_back(new KmsAIController());

    lpEnemyController = vLpEnemyController[1];
    lpEnemyController->Init();
    lpEnemyController->SetController(lpPlanetSSJ);

    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");
    lpBackImage2 = ImageManager::GetSingleton()->FindImage("SPACE");
    backgroundMover = 0;
    
    elapsedTime = 0;

    currStage = STAGE_STATE::LOADING;
    nextStage = STAGE_STATE::STAGE1;
    isBossAlive = false;
    
    lpLoadingCat = new Animation();
    lpLoadingCat->Change("LOADING_CAT", 4, true, false);
    catPos = { -50, 400 };
            
    backgroundMover = 0;
 
    //플레이어 
    lpPlayerController = new PlayerController();
    lpPlayerController->Init();
    lpPlayerController->SetController(lpPlayer);

    //적 보스    
    //lpEnemyController = new SSJAIController();
    //lpEnemyController->Init();
    //lpEnemyController->SetController(lpPlanetSSJ);
    lpPlayer->SetTarget(lpPlanetSSJ);

    lpUIobject = new UIobject();
    lpUIobject->Init();
    lpUIobject->SetPlayer(lpPlayer);
    lpUIobject->SetEnemy(lpEnemyController->GetController());
    
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
    if (lpEnemyController)
    {
        lpEnemyController->Release();
        delete lpEnemyController;
        lpEnemyController = nullptr;
    }

    if (!vEnemys.empty())
    {
        for (int i = 0; i < vEnemys.size(); i++)
        {
            vEnemys[i]->Release();
            delete vEnemys[i];
        }
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

    if (lpUIobject)
    {
        lpUIobject->Release();
        delete lpUIobject;
        lpUIobject = nullptr;
    }

    if (lpPlayerController)
    {
        lpPlayerController->Release();
        delete lpPlayerController;
        lpPlayerController = nullptr;
    }

    //벡터로 바꾼거 릴리즈
}

void InGameScene::Update(float deltaTime)
{
    

    CheckCollision();
    
    if (!isBossAlive)
    {
        switch (currStage)
        {
        case STAGE_STATE::LOADING:
            if (elapsedTime > 10)
            {                
                currStage = nextStage;
                elapsedTime = 0;
                isBossAlive = true;
                catPos.x = -50;
            }
            else
            {
                lpLoadingCat->Update(deltaTime);
                catPos.x += deltaTime * 100;
            }
            break;
        case STAGE_STATE::STAGE1:
            currStage = STAGE_STATE::LOADING;
            nextStage = STAGE_STATE::STAGE2;
            
            lpEnemyController = vLpEnemyController[0];
            lpEnemyController->Init();
            lpEnemyController->SetController(lpJinHwang);
            lpUIobject->SetEnemy(lpEnemyController->GetController());
            lpEnemyController->GetController()->SetHp(lpEnemyController->GetController()->GetHp());
            lpPlayer->SetTarget(lpJinHwang);

            //missile release
            //vector<Missile*>& vLpEnemyMissile = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::ENEMY);
            //for (int i = 0; i < vLpEnemyMissile.size(); ++i)
            //{
            //    MissileManager::GetSingleton()->DisableMissile(UNIT_KIND::ENEMY, i);
            //}
            
            elapsedTime = 0;
            break;
        case STAGE_STATE::STAGE2:
            currStage = STAGE_STATE::LOADING;
            nextStage = STAGE_STATE::STAGE3;
            
            lpEnemyController = vLpEnemyController[2];
            lpEnemyController->Init();
            lpEnemyController->SetController(lpPlanet04);
            lpUIobject->SetEnemy(lpEnemyController->GetController());
            lpEnemyController->GetController()->SetHp(lpEnemyController->GetController()->GetHp());
            lpPlayer->SetTarget(lpPlanet04);

            //missile release

            elapsedTime = 0;
            break;
        case STAGE_STATE::STAGE3:
            currStage = STAGE_STATE::LOADING;
            nextStage = STAGE_STATE::STAGE4;
            
            lpEnemyController = vLpEnemyController[3];
            lpEnemyController->Init();
            lpEnemyController->SetController(lpPlanetKMS);
            lpUIobject->SetEnemy(lpEnemyController->GetController());
            lpEnemyController->GetController()->SetHp(lpEnemyController->GetController()->GetHp());
            lpPlayer->SetTarget(lpPlanetKMS);

            //missile release

            elapsedTime = 0;
            break;
        case STAGE_STATE::STAGE4:
            currStage = STAGE_STATE::LOADING;
            nextStage = STAGE_STATE::STAGE4;
            SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::ENDING);
            break;
             
        }
    }

    if (elapsedTime > 10 && isBossAlive == true)
    {
        if (lpEnemyController) lpEnemyController->Update(deltaTime);
       
    }

    if(isBossAlive)
        if (lpPlayerController) lpPlayerController->Update(deltaTime);
       
    

    for (int i =0; i <vEnemys.size(); i++)
    {
        vEnemys[i]->Update(deltaTime);
    }

    
    //아이템 등장시점도 조절 필요
    if (lpItem) lpItem->Update(deltaTime);
    if (lpUIobject) lpUIobject->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime);
    EffectManager::GetSingleton()->Update(deltaTime);

    backgroundMover += 300 *deltaTime;
    if (backgroundMover >= 800) backgroundMover = 0;

    if (KeyManager::GetSingleton()->IsKeyDownOne('E'))
    {
        if (lpUIobject->GetBombAmount() < 0)
        {
            lpUIobject->SetBombAmount(0);
        }
        else
            lpUIobject->SetBombAmount(lpUIobject->GetBombAmount() - 1);
    }

    elapsedTime += deltaTime;

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

    for (int i = 0; i < vEnemys.size(); i++)
    {
        vEnemys[i]->Render(hBackDC);
    }

    if (lpItem) lpItem->Render(hBackDC);

    if (lpUIobject) lpUIobject->Render(hBackDC);
    EffectManager::GetSingleton()->Render(hBackDC);
    MissileManager::GetSingleton()->Render(hBackDC);
    
    if (currStage == STAGE_STATE::LOADING)
    {
        lpLoadingCat->Render(hBackDC, catPos.x, catPos.y);
    }
        

    lpBackBuffer->Render(hdc);
   
}

void InGameScene::CheckCollision()
{
    vector<Missile*>& vLpEnemyMissile = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::ENEMY);
    vector<Missile*>& vLpPlayerMissile = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::PLAYER);

    float distance = 100.0f;
    float dX = 0;
    float dY = 0;


    //적이 플레이어를 떄릴때
    for (int i = 0; i < vLpEnemyMissile.size();)
    {
        dX = vLpEnemyMissile[i]->pos.x + vLpEnemyMissile[i]->deltaMove.deltaPos.x - lpPlayer->pos.x;
        dY = vLpEnemyMissile[i]->pos.y + vLpEnemyMissile[i]->deltaMove.deltaPos.y - lpPlayer->pos.y;
        distance = sqrt(dX * dX + dY * dY);

        if (distance <= vLpEnemyMissile[i]->collider.width / 2 + lpPlayer->collider.width / 2)
        {
            EffectManager::GetSingleton()->PlayImage({ vLpEnemyMissile[i]->pos.x + vLpEnemyMissile[i]->deltaMove.deltaPos.x , vLpEnemyMissile[i]->pos.y + vLpEnemyMissile[i]->deltaMove.deltaPos.y }, "EFFECT_01", 10);
            MissileManager::GetSingleton()->DisableMissile(UNIT_KIND::ENEMY, i);
            //체력이 0이되면 데미지를 받아도 체력 0
            if (lpPlayerController->GetController()->GetHp() <= 0)
            {
                lpUIobject->SetLifeAmount(lpUIobject->GetLifeAmount()-1);
                lpPlayerController->GetController()->SetHp(lpUIobject->GetPlayerMaxHp()); // 여기서 플레이어 체력을 풀로 채워줘야함
                if (lpUIobject->GetLifeAmount() < 0)
                {
                    lpPlayerController->GetController()->SetHp(0);
                    //플레이어의 사망 체크를 여기서 표현
                    EffectManager::GetSingleton()->Explosion(lpPlayer->pos, ImageManager::GetSingleton()->FindImage("SPACESHIP_IDLE"), 0, 20, 8, 8);
                }
            }
            //체력이 0이 아니면 10씩 데미지를 줌 
            else                            // 적이 플레이어에게 주는 데미지값 :10
                lpPlayerController->GetController()->SetHp(lpPlayerController->GetController()->GetHp() - 10);
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
            //체력이 0이되면 데미지를 받아도 체력 0
            if (lpEnemyController->GetController()->GetHp() <= 0)
            {
                lpEnemyController->GetController()->SetHp(0);
                //적의 사망 체크를 여기서 표현
                isBossAlive = false;
                elapsedTime = 0;
            }
            //체력이 0이 아니면 10씩 데미지를 줌
            else                               // 내가 적에게 주는 데미지값 :10
                lpEnemyController->GetController()->SetHp(lpEnemyController->GetController()->GetHp() - 10);

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
    }

}