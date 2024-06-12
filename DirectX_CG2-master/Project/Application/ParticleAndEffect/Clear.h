#pragma once
#pragma once
#include"WinApp.h"
#include"Sprite.h"
#include"MyMath.h"

class Clear
{
public:

	void Initialize(SpriteCommon* spriteCommon);

	void Update();

	void OnFlag();

	void Draw();

private:

	//スプライト
	std::unique_ptr<Sprite> clearSP;

	DirectX::XMFLOAT2 position = { 1200.0f,0.0f };
	const float frameMax = 30.0f;
	float frame = 0.0f;

	bool isClear = false;
};
