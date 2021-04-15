#include "Keymannager.h"
#include<windows.h>
Keymannager::Keymannager()
{
    isKeyUp.reset();
    isKeyState.reset();
    isKeyDown.reset();
}

Keymannager::~Keymannager()
{
   
}

bool Keymannager::IsKeyDownOne(int input)
{
    short keybutton = GetAsyncKeyState(input);
    if (keybutton & 0x8000)
    {
        if (isKeyState[input]==false)
        {
            isKeyDown[input] = true;
        }
        else {
            isKeyDown[input] = false;
        }
        isKeyState[input] == true;
    }
    else {
        isKeyState[input] == false;
        isKeyDown[input] = false;
    }
    return  isKeyDown[input];
}

bool Keymannager::IsKeyUPOne(int input)
{
    short keybutton = GetAsyncKeyState(input);
    if (!(keybutton & 0x8000))
    {
        if (isKeyState[input] == true)
        {
            isKeyUp[input] = true;
        }
        else {
            isKeyUp[input] = false;
        }
        isKeyState[input] == false;
    }
    else {
        isKeyState[input] == false;
        isKeyUp[input] = false;
    }
    return  isKeyDown[input];
}

bool Keymannager::IsKeyDownStatus(int input)
{
    short keybutton = GetAsyncKeyState(input);
    if (keybutton & 0x8000)
    {
        isKeyState[input] == true;
    }
    else {
        isKeyState[input] == false;
    }
    return   isKeyState[input];
}
