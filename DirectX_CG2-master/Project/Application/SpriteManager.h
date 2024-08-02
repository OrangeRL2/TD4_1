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
		HP,
		stamina,
		staminaBars,
		HPHUD,
		HPHUDDecal1,
		HPHUDDecal2,
		Pause,
		Tutorial,
		Boss,
	};

private:
	SpriteCommon* spriteCommon_ = nullptr;
};
