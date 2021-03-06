#include "AIController.h"

class Unit;
class AlienAIController :public AIController
{
private:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual void SetUnit(Unit* lpUnit);
};

