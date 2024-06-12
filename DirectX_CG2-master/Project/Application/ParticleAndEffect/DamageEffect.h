#pragma once
#include"WinApp.h"
#include"Sprite.h"

class DamageEffect
{
public:

	void Initialize(SpriteCommon* spriteCommon);

	void Update();

	void Draw();

	void SetTimer();

private:

	//スプライト
	std::unique_ptr<Sprite> whiteSP;

	//経過時間＆透明度
	const float transTimerMax = 1.0f;
	const float transTimerVal = 0.05f;
	float transTimer = 0.0f;

};

