#include "SpriteManager.h"

void SpriteManager::Initialize(SpriteCommon* spriteCommon) {

	spriteCommon_ = spriteCommon;

	spriteCommon->LoadTexture(white1x1, "white1x1.png");
	spriteCommon->LoadTexture(GameOver, "GameOver.png");
	spriteCommon->LoadTexture(Clear, "Clear.png");
	spriteCommon->LoadTexture(sceneChange, "sceneChange.png");
	spriteCommon->LoadTexture(numbersA, "numbersA.png");
	spriteCommon->LoadTexture(numbersB, "numbersB.png");
	spriteCommon->LoadTexture(space, "space.png");
	spriteCommon->LoadTexture(title, "Title.png");

}
