#include "SceneManager.h"
#include "BridgeShooter.h"
#include "GameScene.h"
#include "Title.h"
#include "InGameScene.h"
#include "SelectPlayer.h"

HRESULT SceneManager::Init()
{
	for (int i = 0; i <(int)SCENE_STATE::NONE; ++i)
	{
		switch (i)
		{
		case (int)SCENE_STATE::TITLE:
			scenes[i] = new Title();
			scenes[i]->Init();
			break;
		case (int)SCENE_STATE::SELECT:
			scenes[i] = new SelectPlayer();
			scenes[i]->Init();
			break;
		case (int)SCENE_STATE::INGAME:
			scenes[i] = new InGameScene();
			scenes[i]->Init();
			break;
		case (int)SCENE_STATE::NONE:
			break;
		}
	}

	currScene = SCENE_STATE::TITLE;
	return S_OK;
}

void SceneManager::Release()
{
	for (int i = 0; i < (int)SCENE_STATE::NONE; ++i)
	{
		if (scenes[i])
		{
			scenes[i]->Release();
			delete scenes[i];
			scenes[i] = nullptr;
		}
	}
}

void SceneManager::Update(float deltaTime)
{
	scenes[(int)currScene]->Update(deltaTime);
}

void SceneManager::Render(HDC hdc)
{
	scenes[(int)currScene]->Render(hdc);
}

void SceneManager::ChangeScene()
{
	if (currScene == SCENE_STATE::TITLE)
	{
		currScene = SCENE_STATE::SELECT;

	}
		
	else if (currScene == SCENE_STATE::SELECT)
	{
		currScene = SCENE_STATE::INGAME;
		
	}
		
	else if (currScene == SCENE_STATE::INGAME)
	{
		currScene = SCENE_STATE::TITLE;
		
	}
		
}
