#pragma once
#include "Singleton.h"
#include <Windows.h>

class GameScene;
class SceneManager : public Singleton<SceneManager>
{
public:
	enum class SCENE_STATE
	{
		TITLE,
		SELECT,
		INGAME,
		NONE
	};

private:
	GameScene* scenes[(int)SCENE_STATE::NONE];
	SCENE_STATE currScene;
	SCENE_STATE lastScene;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
	void ChangeScene(SCENE_STATE scene);

};