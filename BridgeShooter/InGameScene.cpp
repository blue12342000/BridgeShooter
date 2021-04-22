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
    slowScale = 1;

    elapsedTime = 0;
    backgroundMover = 0;
    currStage = STAGE_STATE::LOADING;
    nextStage = STAGE_STATE::STAGE1;

    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");

    lpLoadingCat = new Animation();
    lpLoadingCat->Change("LOADING_CAT", 4, true, false);
    catPos = { -50, 400 };

    lpPlayerController = new PlayerController();
    lpPlayerController->Init();
    switch (DataManager::GetSingleton()->GetSelectedCharacter())
    {
    case (int)DataManager::CHARACTER_CODE::YELLOW:
        lpPlayerController->SetUnit(new SpaceShip());
        break;
    case (int)DataManager::CHARACTER_CODE::RED:
        lpPlayerController->SetUnit(new SpaceShip_Red());
        break;
    case (int)DataManager::CHARACTER_CODE::GRAY:
        lpPlayerController->SetUnit(new SpaceShip_Gray());
        break;
    }
    

    mLpBossController.insert(make_pair(STAGE_STATE::STAGE1, new JinHwangAIContoller()));
    mLpBossController.insert(make_pair(STAGE_STATE::STAGE2, new SSJAIController()));
    mLpBossController.insert(make_pair(STAGE_STATE::STAGE3, new Planet04AIcontroller()));
    mLpBossController.insert(make_pair(STAGE_STATE::STAGE4, new KmsAIController()));
    mLpBossController[STAGE_STATE::STAGE1]->SetUnit(new JinHwang());
    mLpBossController[STAGE_STATE::STAGE2]->SetUnit(new Planet_SSJ());
    mLpBossController[STAGE_STATE::STAGE3]->SetUnit(new Planet04());
    mLpBossController[STAGE_STATE::STAGE4]->SetUnit(new Planet_KMS());

    vEnemys.push_back(new AlienBlue());
    vEnemys.push_back(new AlienGreen());
    vEnemys.push_back(new AlienRed());
    vEnemys.push_back(new AlienYellow());
    for (int i = 0; i < vEnemys.size(); i++)
    {
        vLpMobController.push_back(new AlienAIController);
        vLpMobController[i]->SetUnit(vEnemys[i]);
    }

    vItems.resize(2);
    for (int i = 0; i < vItems.size(); ++i)
    {
        vItems[i] = new Item();
        vItems[i]->Init();
        vItems[i]->SetIsActive(false);
    }

    lpUIobject = new UIobject();
    lpUIobject->Init();
    lpUIobject->SetPlayer(lpPlayerController->GetUnit());
    
 return S_OK;
}

void InGameScene::Release()
{
    MissileManager::GetSingleton()->ClearActiveMissile();
    EffectManager::GetSingleton()->Release();

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

    //is this right
    if (!mLpBossController.empty())
    {
        for (auto& pair : mLpBossController)
        {
            pair.second->Release();
        }
        mLpBossController.clear();
    }

    for (auto& item : vItems)
    {
        delete item;
    }
    vItems.clear();
}

void InGameScene::Update(float deltaTime)
{
    switch (currStage)
    {
    case STAGE_STATE::LOADING:
        if (elapsedTime > 10)
        {
            if (nextStage != STAGE_STATE::NONE)
            {
                lpCurrentBossController = mLpBossController[nextStage];
                lpCurrentBossController->Init();
                lpCurrentBossController->GetUnit()->Heal(U_MAX_BOSS_HP);
                lpCurrentBossController->GetUnit()->SetTarget(lpPlayerController->GetUnit());
                lpUIobject->SetEnemy(lpCurrentBossController->GetUnit());
                catPos.x = -50;
                currStage = nextStage;
                nextStage = (STAGE_STATE)((int)nextStage + 1);
                elapsedTime = 0;
            }
            else
            {
                SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::CLEAR);
            }
        }
        else
        {
            if (nextStage != STAGE_STATE::NONE)
            {
                lpLoadingCat->Update(deltaTime);
                catPos.x += deltaTime * 100;
            }
        }
        break;
    case STAGE_STATE::STAGE1:
    case STAGE_STATE::STAGE2:
    case STAGE_STATE::STAGE3:
    case STAGE_STATE::STAGE4:
        if (!lpCurrentBossController->IsReady() && elapsedTime > 10) lpCurrentBossController->SetIsReady(true);

        if (lpPlayerController->IsReady() && lpCurrentBossController->IsReady())
        {
            // 보스 <> 플레이어
            UnitCollision(lpPlayerController->GetUnit()->GetUnitKind(), lpCurrentBossController);
            UnitCollision(lpCurrentBossController->GetUnit()->GetUnitKind(), lpPlayerController);
        }
        for (int i = 0; i < vLpMobController.size(); i++)
        {
            if (lpPlayerController->IsReady() && vLpMobController[i]->IsReady())
            {
                // 잡몹 <> 플레이어
                UnitCollision(lpPlayerController->GetUnit()->GetUnitKind(), vLpMobController[i]);
            }
        }
        if (!vLpMobController.empty()) UnitCollision(vLpMobController[0]->GetUnit()->GetUnitKind(), lpPlayerController);

        for (auto it = vItems.begin(); it != vItems.end(); ++it)
        {
            if ((*it)->IsActive() && !ItemCollision(lpPlayerController->GetUnit(), *it))
            {
                (*it)->Update(deltaTime / slowScale);
            }
        }

        if (lpCurrentBossController->IsReady()) lpCurrentBossController->Update(deltaTime / slowScale);
        if (lpPlayerController && lpPlayerController->IsReady()) lpPlayerController->Update(deltaTime);

        // 몹 이동
        float minDistance = FLT_MAX, distance;
        Unit* lpEnemy = nullptr;
        POINTFLOAT p1,p2;
        for (int i = 0; i < vLpMobController.size(); i++)
        {
            if (vLpMobController[i]->IsReady())
            {
                p1 = vLpMobController[i]->GetUnit()->pos;
                p2 = lpPlayerController->GetUnit()->pos;
                distance = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
                if (minDistance > distance)
                {
                    minDistance = distance;
                    lpEnemy = vLpMobController[i]->GetUnit();
                }

                if (vLpMobController[i]->GetUnit()->IsAlive())
                {
                    vLpMobController[i]->Update(deltaTime / slowScale);
                }

                if (!vLpMobController[i]->GetUnit()->IsAlive()
                    || vLpMobController[i]->GetUnit()->pos.x < WINSIZE_LEFT || vLpMobController[i]->GetUnit()->pos.x > WINSIZE_RIGHT
                    || vLpMobController[i]->GetUnit()->pos.y < WINSIZE_TOP || vLpMobController[i]->GetUnit()->pos.y > WINSIZE_BOTTOM)
                {
                    KillAlien(i);
                }
            }
        }
        p1 = lpCurrentBossController->GetUnit()->pos, p2 = lpPlayerController->GetUnit()->pos;
        distance = (p2.x - p1.x)* (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
        if (minDistance > distance)
        {
            lpEnemy = lpCurrentBossController->GetUnit();
        }
        lpPlayerController->GetUnit()->SetTarget(lpEnemy);

        if ((rand() % 1000000) <= 100)
        {
            CreateAlien(rand() % vLpMobController.size());
        }

        break;
    }

    backgroundMover += 300 * deltaTime / slowScale;
    if (backgroundMover >= 800) backgroundMover = 0;
        
    if (lpUIobject) lpUIobject->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime / slowScale);
    EffectManager::GetSingleton()->Update(deltaTime / slowScale);
    elapsedTime += deltaTime / slowScale;

    slowTimer -= deltaTime;
    if (slowTimer < 0)
    {
        slowTimer = 0;
        slowScale = 1;
    }

    if (lpPlayerController && !lpPlayerController->GetUnit()->IsAlive() && DataManager::GetSingleton()->GetLifeAmount() == 0)
    {
        SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::ENDING);
        DataManager::GetSingleton()->SetLifeAmount(3);
    }
    if (KeyManager::GetSingleton()->IsKeyDownOne(VK_ESCAPE))
    {
        SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::TITLE);
        currStage = STAGE_STATE::LOADING;
        DataManager::GetSingleton()->SetLifeAmount(3);

    }
}


void InGameScene::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();

    if (lpBackImage)
    {
        lpBackImage->Render(hBackDC, 0, backgroundMover);
        lpBackImage->Render(hBackDC, 0, -800 + backgroundMover);
    }

    for (auto item : vItems)
    {
        item->Render(hBackDC);
    }

    for (int i = 0; i < vLpMobController.size(); i++)
    {
        if (vLpMobController[i]->IsReady())
        {
            vLpMobController[i]->Render(hBackDC);
        }
    }

    if (lpPlayerController->IsReady()) lpPlayerController->Render(hBackDC);
    if (lpCurrentBossController && lpCurrentBossController->IsReady())lpCurrentBossController->Render(hBackDC);

    MissileManager::GetSingleton()->Render(hBackDC);
    EffectManager::GetSingleton()->Render(hBackDC);

    if (lpUIobject) lpUIobject->Render(hBackDC);
    
    if (currStage == STAGE_STATE::LOADING)
    {
        lpLoadingCat->Render(hBackDC, catPos.x, catPos.y);
    }

    lpBackBuffer->Render(hdc);
}

void InGameScene::UnitCollision(UNIT_KIND attackerKind, Controller* target)
{
    vector<Missile*>& vLpMissile = MissileManager::GetSingleton()->GetLpMissiles(attackerKind);
    Unit* lpUnit = target->GetUnit();

    if (!lpUnit->IsAlive()) return;

    float distance = FLT_MAX;
    float dX = 0;
    float dY = 0;

    for (int i = 0; i < vLpMissile.size();)
    {
        dX = vLpMissile[i]->pos.x - lpUnit->pos.x;
        dY = vLpMissile[i]->pos.y - lpUnit->pos.y;
        distance = sqrt(dX * dX + dY * dY);

        if (distance <= vLpMissile[i]->collider.width / 2 + lpUnit->collider.width / 2)
        {
            EffectManager::GetSingleton()->PlayImage(vLpMissile[i]->pos, "EFFECT_01", 10);
            //체력이 0이되면 데미지를 받아도 체력 0
            if (target->GetUnit()->Hit(vLpMissile[i]->GetDamage()))
            {
                // 죽었다
                EffectManager::GetSingleton()->Explosion(lpUnit->pos, lpUnit->GetLpAnimation(), 20, 15, 15);
                if (lpUnit->GetUnitKind() == UNIT_KIND::PLAYER)
                {
                    MissileManager::GetSingleton()->ClearActiveMissile();
                    if (DataManager::GetSingleton()->UseLife())
                    {
                        lpUnit->Heal(999999);
                        target->GetUnit()->SetIsReady(false);
                        target->GetUnit()->SetInetia(true);
                        target->GetUnit()->pos = { WINSIZE_WIDTH / 2.0f, WINSIZE_HEIGHT + 300 };
                    }
                    else
                    {
                        lpPlayerController->SetIsReady(false);
 
                    }
                }
                else if (lpUnit->GetUnitKind() == UNIT_KIND::ENEMY)
                {
                    target->SetIsReady(false);
                    for (int i = 0; i < vItems.size(); ++i)
                    {
                        if (!vItems[i]->IsActive())
                        {
                            vItems[i]->Init();
                            vItems[i]->SetIsActive(true);
                            vItems[i]->pos = lpUnit->pos;
                            break;
                        }
                    }
                }
                else if (lpUnit->GetUnitKind() == UNIT_KIND::BOSS)
                {
                    MissileManager::GetSingleton()->ClearActiveMissile();
                    target->SetIsReady(false);
                    elapsedTime = 0;
                    currStage = STAGE_STATE::LOADING;
                }
                break;
            }
            else
            {
                // 살았다
                MissileManager::GetSingleton()->DisableMissile(attackerKind, i);
            }
        }
        else
        {
            ++i;
        }
    }
}

bool InGameScene::ItemCollision(Unit* target, Item* item)
{
    float distance;
    POINTFLOAT p1 = target->pos, p2 = item->pos;
    distance = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);

    if (distance < pow(target->collider.width + item->collider.width, 2))
    {
        // 충돌 아이템 사용
        switch (item->GetItemType())
        {
        case ITEM_TYPE::POWER_UP:
            target->ChangeFactoryLine(1, false);
            break;
        case ITEM_TYPE::BOMB:
            //DataManager::GetSingleton()->SetBombAmount(DataManager::GetSingleton()->GetBombAmount() + 1);
            MissileManager::GetSingleton()->ClearActiveMissile(target->GetUnitKind());
            break;
        case ITEM_TYPE::HP_POTION:
            target->Heal(100);
            break;
        case ITEM_TYPE::SPEED_UP:
            slowTimer = 5;
            slowScale = 5;
            break;
        }
        item->SetIsActive(false);
        return true;
    }
    return false;
}

void InGameScene::KillAlien(int indexNum)
{
    if (!vLpMobController.empty()&& (indexNum>=0)&& (indexNum < vLpMobController.size()))
    {
       vLpMobController[indexNum]->SetIsReady(false);
       EffectManager::GetSingleton()->Explosion(vLpMobController[indexNum]->GetUnit()->pos, vLpMobController[indexNum]->GetUnit()->GetLpAnimation(), 10, 4, 4);
    }
}

void InGameScene::CreateAlien(int indexNum)
{
    if (!vLpMobController[indexNum]->IsReady())
    {
        vLpMobController[indexNum]->SetIsReady(true);
        vLpMobController[indexNum]->GetUnit()->Init();
    }
}