#pragma once
#include "Singleton.h"
#include <bitset>
#include <Windows.h>

#define MAX_INPUT_COUNT 256

using namespace std;

class KeyManager :public Singleton<KeyManager>
{
private:
	bitset<MAX_INPUT_COUNT> isKeyUp;
	bitset<MAX_INPUT_COUNT> isKeyDown;
	
public:
	HRESULT Init();

	bool IsKeyDownOne(int input);
	bool IsKeyUpOne(int input);
	bool IsKeyDownStay(int input);
};

