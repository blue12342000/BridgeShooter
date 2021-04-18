#include "EffectManager.h"
#include "BridgeShooter.h"
#include "Image.h"

HRESULT EffectManager::Init()
{
	vEffects.reserve(10);
	return S_OK;
}

void EffectManager::Update(float deltaTime)
{
	for (int i = 0; i < vEffects.size();)
	{
		if (vEffects[i].type == EFFECT_TYPE::FILELOAD) vEffects[i].frame = (int)vEffects[i].frameTime;
		else if (vEffects[i].type == EFFECT_TYPE::EXPLOSION)
		{
			for (auto& split : vEffects[i].vSplitPos)
			{
				split.pos.x += cosf(split.angle) * split.speed * deltaTime;
				split.pos.y += sinf(split.angle) * split.speed * deltaTime;
			}
		}

		if (vEffects[i].frameTime >= vEffects[i].lpImage->GetTotalFrame())
		{
			vEffects.erase(vEffects.begin() + i);
		}
		else
		{
			vEffects[i].frameTime += deltaTime * vEffects[i].fps;
			++i;
		}
	}
}

void EffectManager::Render(HDC hdc)
{
	for (int i = 0; i < vEffects.size(); ++i)
	{
		switch (vEffects[i].type)
		{
		case EFFECT_TYPE::FILELOAD:
			vEffects[i].lpImage->Render(hdc, vEffects[i].pos.x, vEffects[i].pos.y, vEffects[i].frame, U_IA_CENTER);
			break;
		case EFFECT_TYPE::EXPLOSION:
			for (int l = 0; l < vEffects[i].vSplitPos.size(); ++l)
			{
				if (isDebugMode)
				{
					Rectangle(hdc, vEffects[i].vSplitPos[l].pos.x, vEffects[i].vSplitPos[l].pos.y,
						vEffects[i].vSplitPos[l].pos.x + vEffects[i].lpImage->GetWidth() / vEffects[i].splitX,
						vEffects[i].vSplitPos[l].pos.y + vEffects[i].lpImage->GetHeight() / vEffects[i].splitY);
				}
				vEffects[i].lpImage->SplitRender(hdc, { (int)vEffects[i].vSplitPos[l].pos.x, (int)vEffects[i].vSplitPos[l].pos.y }, vEffects[i].splitX, vEffects[i].splitY, l, vEffects[i].frame);
			}

			break;
		case EFFECT_TYPE::FADEOUT:
			//vEffects[i].lpImage->AlphaRender(hdc, vEffects[i].pos.x, vEffects[i].pos.y);
			break;
		}
	}
}

void EffectManager::PlayImage(POINTFLOAT pos, string imageKey, int fps)
{
	Effect effect;
	effect.type = EFFECT_TYPE::FILELOAD;
	effect.pos = pos;
	effect.frame = 0;
	effect.frameTime = 0;
	effect.fps = fps;
	effect.lpImage = ImageManager::GetSingleton()->FindImage(imageKey);
	vEffects.push_back(effect);
}

void EffectManager::Explosion(POINTFLOAT pos, Image* lpImage, int frame, int fps, int splitX, int splitY)
{
	Effect effect;
	effect.type = EFFECT_TYPE::EXPLOSION;
	effect.pos = pos;
	effect.frame = frame;
	effect.frameTime = 0;
	effect.fps = fps;
	effect.lpImage = lpImage;
	effect.vSplitPos.resize(splitX * splitY);
	effect.splitX = splitX;
	effect.splitY = splitY;

	int width = lpImage->GetWidth();
	int height = lpImage->GetHeight();
	POINTFLOAT offset;
	for (int y = 0; y < splitY; ++y)
	{
		for (int x = 0; x < splitX; ++x)
		{
			offset.x = pos.x + rand() % (width / splitX) - (width / splitX);
			offset.y = pos.y + rand() % (height / splitY) - (height / splitY);;

			effect.vSplitPos[splitX * y + x] = { pos.x - width / 2 + width / splitX * x, pos.y - height / 2 + height / splitY * y };
			effect.vSplitPos[splitX * y + x].angle = atan2(effect.vSplitPos[splitX * y + x].pos.y - offset.y, effect.vSplitPos[splitX * y + x].pos.x - offset.x);
			effect.vSplitPos[splitX * y + x].speed = 20;
		}
	}

	vEffects.push_back(effect);
}

void EffectManager::FadeOut(POINTFLOAT pos, Image* lpImage, int frame, int fps, int splitX, int splitY)
{
	Effect effect;
	effect.type = EFFECT_TYPE::FADEOUT;
	effect.pos = pos;
	effect.frame = frame;
	effect.frameTime = 0;
	effect.fps = fps;
	effect.lpImage = lpImage;
	vEffects.push_back(effect);
}
