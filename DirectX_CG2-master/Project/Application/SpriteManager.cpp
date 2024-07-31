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
	spriteCommon->LoadTexture(HP, "HP.png");
	spriteCommon->LoadTexture(stamina, "stamina.png");
	spriteCommon->LoadTexture(staminaBars, "stamina2v2.png");
	spriteCommon->LoadTexture(HPHUD, "HUD.png");
	spriteCommon->LoadTexture(HPHUDDecal1, "HUD2.png");
	spriteCommon->LoadTexture(HPHUDDecal2, "HUD3.png");
	spriteCommon->LoadTexture(Pause, "Pause.png");
	spriteCommon->LoadTexture(Tutorial, "Tutorial.png");

}
