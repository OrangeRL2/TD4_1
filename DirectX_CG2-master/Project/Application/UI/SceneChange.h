#pragma once
#include "Sprite.h"

class SceneChange {

public:

	void Initialize(SpriteCommon* spriteCommon, const bool first);

	void Update();

	void Draw();

	void SetIsReduction(const bool reduction) { isReduction = reduction; }

	const bool GetCompleted() { return isCompleted; }
	const bool GetIsChange() { return isChange; }

private:

	//スプライト
	std::unique_ptr<Sprite> SP[5];

	//サイズ
	const float textureSize = 256;
	const float MaxSize = textureSize * 10;
	float size = 0.0f;

	//イージング用フレーム
	const float MaxFrame = 90.0f;
	float frame = 0.0f;

	//遷移の種類
	const int typeNum = 3;

	const float MaxWaitTime = 30.0f;
	float waitTime = MaxWaitTime;

	//シーン遷移縮小フラグ
	bool isReduction = false;
	//シーン遷移中フラグ
	bool isChange = false;
	//遷移完了フラグ
	bool isCompleted = false;

};