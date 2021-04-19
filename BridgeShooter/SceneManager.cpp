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
			break;
		case (int)SCENE_STATE::SELECT:
			scenes[i] = new SelectPlayer();
			break;
		case (int)SCENE_STATE::INGAME:
			scenes[i] = new InGameScene();
			break;
		case (int)SCENE_STATE::NONE:
			break;
		}
	}

	currScene = SCENE_STATE::NONE;
	ChangeScene(SCENE_STATE::TITLE);
	
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

void SceneManager::ChangeScene(SCENE_STATE scene)
{
	//nullptr이면 init, 이미 생성되어있으면 씬만 바꾸기 ->reset함수호출
	//씬리셋해주는 함수 - 각씬마다. ->동적할당 없어야함(꼭필요하면 넣고 릴리즈)

	lastScene = currScene;
	currScene = scene;
	
	if(lastScene != SCENE_STATE::NONE)
		scenes[(int)lastScene]->Release();
	scenes[(int)currScene]->Init();

}
