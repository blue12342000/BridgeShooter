#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

enum class EFFECT_TYPE
{
	FILELOAD,
	EXPLOSION,
	BLACKHOLE,
	FADEOUT,
	NONE
};

struct SplitBox
{
	POINTFLOAT pos;
	float angle;
	float destAngle;
	int speed;
};

class Image;
struct Effect
{
	EFFECT_TYPE type;
	int fps;
	int frame;
	float frameTime;
	Image* lpImage;
	string imageKey;
	POINTFLOAT pos;

	int splitX;
	int splitY;
	vector<SplitBox> vSplitPos;
};

class EffectManager : public Singleton<EffectManager>
{
private:
	vector<Effect> vEffects;

public:
	HRESULT Init();
	void Update(float deltaTime);
	void Render(HDC hdc);

	void PlayImage(POINTFLOAT pos, string imageKey, int fps);
	void Explosion(POINTFLOAT pos, Image* lpImage, int frame, int fps, int splitX, int splitY);
	void Blackhole(POINTFLOAT pos, Image* lpImage, int frame, int fps, int splitX, int splitY);
	void FadeOut(POINTFLOAT pos, Image* lpImage, int frame, int fps, int splitX, int splitY);
};

