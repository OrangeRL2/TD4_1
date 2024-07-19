#pragma once
#include "SpriteCommon.h"

class SpriteManager {

public:
	void Initialize(SpriteCommon* spriteCommon);

	enum Sprites {
		white1x1,
		GameOver,
		Clear,
		sceneChange,
		numbersA,
		numbersB,
		space,
		title,
	};

private:
	SpriteCommon* spriteCommon_ = nullptr;
};