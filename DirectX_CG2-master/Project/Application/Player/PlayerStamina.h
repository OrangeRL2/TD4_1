#pragma once
#include"WinApp.h"
#include"Sprite.h"


class PlayerStamina
{
public:

	void Initialize(SpriteCommon* spriteCommon);

	void Update(float playerStamina);

	void Draw();

	void SetTimer();
	void OnUse();

private:

	//スプライト
	std::unique_ptr<Sprite> whiteSP;
	std::unique_ptr<Sprite> whiteSP2;
	float stamina = 500.0f;
	float afterStamina = 500;
	//経過時間＆透明度
	const float transTimerMax = 1.0f;
	const float transTimerVal = 0.05f;
	float transTimer = 0.0f;
	bool useFlag = false;

};

