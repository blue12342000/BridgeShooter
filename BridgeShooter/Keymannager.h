#pragma once
#include"Singtleton.h"
#include<bitset>

#define maxIndexNum 254


class Keymannager:public Singtleton<Keymannager>
{
private:
	std::bitset<maxIndexNum>isKeyUp;
	std::bitset<maxIndexNum>isKeyDown;
	std::bitset<maxIndexNum>isKeyState;
	
public:
	Keymannager();
	~Keymannager();

	bool IsKeyDownOne(int input);
	bool IsKeyUPOne(int input);
	bool IsKeyDownStatus(int input);
};

