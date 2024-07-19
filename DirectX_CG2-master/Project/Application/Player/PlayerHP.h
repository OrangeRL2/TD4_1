#pragma once
#include"WinApp.h"
#include"Sprite.h"

class PlayerHP
{
public:

	void Initialize(SpriteCommon* spriteCommon);

	void Update();

	void Draw();

	void SetTimer();
	void OnHit();

private:

	//スプライト
	std::unique_ptr<Sprite> whiteSP;
	std::unique_ptr<Sprite> whiteSP2;
	std::unique_ptr<Sprite> whiteSP3;
	float HP = 600.0f;
	float afterHP = 600;
	//経過時間＆透明度
	const float transTimerMax = 1.0f;
	const float transTimerVal = 0.05f;
	float transTimer = 0.0f;
	bool hitFlag = false;

};

