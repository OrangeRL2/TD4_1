#include "PlayerHP.h"

void PlayerHP::Initialize(SpriteCommon* spriteCommon) {
	/*spriteCommon->LoadTexture(3, "HP.png");
	spriteCommon->LoadTexture(4, "stamina.png");
	spriteCommon->LoadTexture(5, "stamina2v2.png");
	spriteCommon->LoadTexture(6, "HUD.png");
	spriteCommon->LoadTexture(7, "HUD2.png");
	spriteCommon->LoadTexture(8, "HUD3.png");*/
	whiteSP = std::make_unique<Sprite>();
	whiteSP->Initialize(spriteCommon, SpriteManager::HP);
	whiteSP->SetAnchorpoint({ 0.0f, 0.0f });
	whiteSP2 = std::make_unique<Sprite>();
	whiteSP2->Initialize(spriteCommon, SpriteManager::HPHUD);
	whiteSP2->SetAnchorpoint({ 0.0f, 0.0f });
}

void PlayerHP::Update() {

	whiteSP->SetPosition({ 100.0f,60.0f });
	whiteSP->SetSize({ HP,16.0f });

	whiteSP2->SetPosition({ 100.0f-37.0f,60.0f-10.0f });
	whiteSP2->SetSize({ 700,64.0f });

	//whiteSP->SetColor({ 0.5f,0.0f,0.0f,transTimer });
	whiteSP->Update();
	//HP -= 0.2f;
	if (hitFlag == true) {
		if (HP > afterHP) {
			HP -= 5.0f;
		}
		if (HP < afterHP) {
			HP = afterHP;
			hitFlag = false;
		}
		if (HP == afterHP) {
			hitFlag = false;
		}
	}

	if (healFlag == true) {
		if (HP < afterHP) {
			HP += 1.0f;
		}
		if (HP > afterHP) {
			HP = afterHP;
			healFlag = false;
		}
		if (afterHP > 600) {
			afterHP = 600;
			healFlag = false;
		}
		if (HP == afterHP) {
			healFlag = false;
		}
	}
}
void PlayerHP::OnHit() {
	hitFlag = true;
	afterHP -= 100;
}

void PlayerHP::OnHeal() {
	if(afterHP<600){
	healFlag = true;
	afterHP += 100;
	}
}

void PlayerHP::Draw() {
	whiteSP2->Draw();
	whiteSP->Draw();
	
}