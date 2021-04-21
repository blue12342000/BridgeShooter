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
        break;
    case (int)DataManager::CHARACTER_CODE::RED:
        lpPlayer = new SpaceShip_Red();
        break;
    case (int)DataManager::CHARACTER_CODE::GRAY:
        lpPlayer = new SpaceShip_Gray();
        break;
    }
    lpPlayer->Init();
    lpPlayer->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT };
       
    lpPlanet04 = new Planet04();
    lpPlanet04->Init();
    lpPlanet04->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 };

    lpPlanetSSJ = new Planet_SSJ();
    lpPlanetSSJ->Init();
    lpPlanetSSJ->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 - 300 };

    lpPlanetKMS = new Planet_KMS();
    lpPlanetKMS->Init();
    lpPlanetKMS->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 };

    lpJinHwang = new JinHwang();
    lpJinHwang->Init();
    lpJinHwang->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 - 300 };


    lpItem = new Item();
    lpItem->Init();
    lpItem->pos = { (float)WINSIZE_WIDTH / 8, (float)WINSIZE_HEIGHT / 7 };

    vLpEnemyController.push_back(new JinHwangAIContoller()); 
    vLpEnemyController.push_back(new SSJAIController());
    vLpEnemyController.push_back(new Planet04AIcontroller());
    vLpEnemyController.push_back(new KmsAIController());

    lpEnemyController = vLpEnemyController[1];
    lpEnemyController->Init();
    lpEnemyController->SetController(lpPlanetKMS); 

    vEnemys.push_back(new AlienBlue());
    vEnemys.push_back(new AlienGreen());
    vEnemys.push_back(new AlienRed());
    vEnemys.push_back(new AlienYellow());
    for (int i = 0; i < vEnemys.size(); i++)
    {
        vLpMobController.push_back(new AlienAIController);
        vLpMobController[i]->SetController(vEnemys[i]);
        vLpMobController[i]->Init();
    }

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
 
    lpPlayerController = new PlayerController();
    lpPlayerController->Init();
    lpPlayerController->SetController(lpPlayer);
    lpPlayer->SetTarget(lpPlanetSSJ);

    lpEnemyController = new JinHwangAIContoller();
    lpEnemyController->Init();
    lpEnemyController->SetController(lpJinHwang);

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
   
    if (!vEnemys.empty())
    {

        for (vector<Unit*>::iterator i = vEnemys.begin();i != vEnemys.end() ;)
        {
            (*i)->Release();
            i=vEnemys.erase(i);
        }

    }
    if (!vLpMobController.empty()) 
    {
        for (vector<Controller*>::iterator i = vLpMobController.begin(); i != vLpMobController.end();)
        {
            (*i)->Release();
            i = vLpMobController.erase(i);
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

  
}

void InGameScene::Update(float deltaTime)
{
    elapsedTime += deltaTime;

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
                //잡몹 세팅
            }
            else
            {
                lpLoadingCat->Update(deltaTime);
                catPos.x += deltaTime * 100;
            }
            break;
        case STAGE_STATE::STAGE1:
            elapsedTime = 0;
            currStage = STAGE_STATE::LOADING;
            nextStage = STAGE_STATE::STAGE2;
            isBossAlive = true;
            lpEnemyController = vLpEnemyController[0];
            lpEnemyController->Init();
            lpEnemyController->SetController(lpJinHwang);
            //적이 죽고나서 바뀌고 다음 스테이지를 시작할때
            //다음 행성에게 에너미를 새로 부여하고 0이었던  체력을 다시 설정.
            lpUIobject->SetEnemy(lpEnemyController->GetController());
            lpEnemyController->GetController()->SetHp(lpEnemyController->GetController()->GetHp());
            lpPlayer->SetTarget(lpJinHwang);

            //vector<Missile*>& vLpEnemyMissile2 = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::ENEMY);
            //for (int i=0; i< vLpEnemyMissile2.size(); ++i)
            //{
            //    MissileManager::GetSingleton()->DisableMissile(UNIT_KIND::ENEMY, i);
            //}

            elapsedTime = 0;
            break;
        case STAGE_STATE::STAGE2:
            currStage = STAGE_STATE::LOADING;
            nextStage = STAGE_STATE::STAGE3;
            isBossAlive = true;
            lpEnemyController = vLpEnemyController[2];
            lpEnemyController->Init();
            lpEnemyController->SetController(lpPlanet04);
            lpPlayer->SetTarget(lpPlanet04);
         //vector<Missile*>& vLpEnemyMissile2 = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::ENEMY);
         //for (int i=0; i< vLpEnemyMissile2.size(); ++i)
         //{
         //    MissileManager::GetSingleton()->DisableMissile(UNIT_KIND::ENEMY, i);
         //}

            elapsedTime = 0;
            break;
        case STAGE_STATE::STAGE3:
            currStage = STAGE_STATE::LOADING;
            nextStage = STAGE_STATE::STAGE4;
            isBossAlive = true;
            lpEnemyController = vLpEnemyController[3];
            lpEnemyController->Init();
            lpEnemyController->SetController(lpPlanetKMS);
            lpPlayer->SetTarget(lpPlanetKMS);
         //vector<Missile*>& vLpEnemyMissile2 = MissileManager::GetSingleton()->GetLpMissiles(UNIT_KIND::ENEMY);
         //for (int i=0; i< vLpEnemyMissile2.size(); ++i)
         //{
         //    MissileManager::GetSingleton()->DisableMissile(UNIT_KIND::ENEMY, i);
         //}

            elapsedTime = 0;
            break;
        case STAGE_STATE::STAGE4:
            currStage = STAGE_STATE::NONE;

            if(elapsedTime > 10)
                SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::ENDING);
            break;
             
        }
    }

    if (elapsedTime > 10 && isBossAlive == true)
    {
        if (lpEnemyController) lpEnemyController->Update(deltaTime);
    }
       
    if (lpPlayerController) lpPlayerController->Update(deltaTime);

    for (int i = 0; i < vLpMobController.size();i++)
    {
        //vLpMobController[i]->Update(deltaTime);
        if ((vEnemys[i]->GetHp() > 0) && ((vEnemys[i]->pos.x > WINSIZE_LEFT) && (vEnemys[i]->pos.x < WINSIZE_RIGHT) &&
            (vEnemys[i]->pos.y > WINSIZE_TOP) && (vEnemys[i]->pos.y < WINSIZE_BOTTOM)))
        {
            vLpMobController[i]->Update(deltaTime);
        }
    }
   

    
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
        vLpMobController[i]->Render(hBackDC);
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


    for (int i = 0; i < vLpEnemyMissile.size();)
    {
        dX = vLpEnemyMissile[i]->pos.x - lpPlayer->pos.x;
        dY = vLpEnemyMissile[i]->pos.y - lpPlayer->pos.y;
        distance = sqrt(dX * dX + dY * dY);

        if (distance <= vLpEnemyMissile[i]->collider.width / 2 + lpPlayer->collider.width / 2)
        {
            EffectManager::GetSingleton()->PlayImage(vLpEnemyMissile[i]->pos, "EFFECT_01", 10);
            MissileManager::GetSingleton()->DisableMissile(UNIT_KIND::ENEMY, i);
            //체력이 0이되면 데미지를 받아도 체력 0
            if (lpPlayerController->GetController()->GetHp() <= 0)
            {
                lpUIobject->SetLifeAmount(lpUIobject->GetLifeAmount()-1);
                lpPlayerController->GetController()->SetHp(lpUIobject->GetPlayerMaxHp()); 
                if (lpUIobject->GetLifeAmount() < 0)
                {
                    lpPlayerController->GetController()->SetHp(0);
                    EffectManager::GetSingleton()->Explosion(lpPlayer->pos, lpPlayer->GetLpAnimation(), 20, 8, 8);
                    //적의 사망 체크를 여기서 표현
                }
            }
            //체력이 0이 아니면 10씩 데미지를 줌
            else                                
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
        dX2 = vLpPlayerMissile[i]->pos.x - lpPlanetSSJ->pos.x;
        dY2 = vLpPlayerMissile[i]->pos.y - lpPlanetSSJ->pos.y;
        distance2 = sqrt(dX2 * dX2 + dY2 * dY2);
        if (distance2 <= vLpPlayerMissile[i]->collider.width / 2 + lpPlanetSSJ->collider.width / 2)
        {
            EffectManager::GetSingleton()->PlayImage(vLpPlayerMissile[i]->pos, "EFFECT_01", 10);
            MissileManager::GetSingleton()->DisableMissile(UNIT_KIND::PLAYER, i);
            if (lpEnemyController->GetController()->GetHp() <= 0)
            {
                //???? ??? ???? ???? ???
                isBossAlive = false;
                lpEnemyController->GetController()->SetHp(0);
                EffectManager::GetSingleton()->Explosion(lpPlanetSSJ->pos, lpPlanetSSJ->GetLpAnimation(), 20, 20, 20);
            }
            else
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

