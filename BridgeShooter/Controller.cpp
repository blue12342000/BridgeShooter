#include "Controller.h"
#include "Unit.h"

void Controller::Init()
{
	mKeyMap.insert(make_pair(INPUT_TYPE::LEFT, UnitEvent{ 'A' }));
	mKeyMap.insert(make_pair(INPUT_TYPE::RIGHT, UnitEvent{ 'D' }));
	mKeyMap.insert(make_pair(INPUT_TYPE::UP, UnitEvent{ 'W' }));
	mKeyMap.insert(make_pair(INPUT_TYPE::DOWN, UnitEvent{ 'S' }));
	mKeyMap.insert(make_pair(INPUT_TYPE::ATTACK, UnitEvent{ VK_SPACE }));
}

void Controller::Release()
{
}

void Controller::Update(float deltaTime)
{
	if (lpUnit) lpUnit->Update(deltaTime);
}

void Controller::Render(HDC hdc)
{
	if (lpUnit) lpUnit->Render(hdc);
}

void Controller::SetController(Unit* lpUnit)
{
	mKeyMap[INPUT_TYPE::LEFT].lpCmd = bind([](Unit& unit) { unit.Translate({ -1, 0 }); }, *lpUnit);
	mKeyMap[INPUT_TYPE::RIGHT].lpCmd = bind([](Unit& unit) { unit.Translate({ 1, 0 }); }, *lpUnit);
	mKeyMap[INPUT_TYPE::UP].lpCmd = bind([](Unit& unit) { unit.Translate({ 0, -1 }); }, *lpUnit);
	mKeyMap[INPUT_TYPE::DOWN].lpCmd = bind([](Unit& unit) { unit.Translate({ 0, 1 }); }, *lpUnit);
	mKeyMap[INPUT_TYPE::ATTACK].lpCmd = bind([](Unit& unit) { unit.Fire(); }, *lpUnit);
}
