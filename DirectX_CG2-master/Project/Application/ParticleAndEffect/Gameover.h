#pragma once
#include"WinApp.h"
#include"Sprite.h"
#include"MyMath.h"

class Gameover
{
public:

	void Initialize(SpriteCommon* spriteCommon);

	void Update();

	void OnFlag();

	void Draw();

private:

	//スプライト
	std::unique_ptr<Sprite> gameoverSP;

	DirectX::XMFLOAT2 position = { 0.0f,-500.0f };
	const float frameMax = 30.0f;
	float frame = 0.0f;
	bool isDraw = false;
};