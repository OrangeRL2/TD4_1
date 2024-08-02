#pragma once
#include"WinApp.h"
#include"Sprite.h"

class DamageEffect
{
public:

	void Initialize(SpriteCommon* spriteCommon);

	void Update();

	void Draw();

	void SetTimer(DirectX::XMFLOAT3 color = { 0.0f,0.0f,0.0f });

private:

	//スプライト
	std::unique_ptr<Sprite> whiteSP;

	//経過時間＆透明度
	const float transTimerMax = 1.0f;
	const float transTimerVal = 0.05f;
	float transTimer = 0.0f;
	DirectX::XMFLOAT3 healColor = { 0.0f,0.0f,0.0f };

};

