#pragma once
#pragma once
#include"WinApp.h"
#include"Sprite.h"
#include"MyMath.h"

class PressSpace
{
public:

	void Initialize(SpriteCommon* spriteCommon);

	void Update();

	void SetIsActive(const bool active) { isActive = active; }

	void Draw();

private:

	//スプライト
	std::unique_ptr<Sprite> SP;

	bool isUIDraw = true;
	bool isActive = true;
	const int MaxUITimer = 30;
	int UITimer = MaxUITimer;
};
