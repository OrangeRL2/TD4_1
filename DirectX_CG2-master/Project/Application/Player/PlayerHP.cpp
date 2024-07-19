#include "PlayerHP.h"

void PlayerHP::Initialize(SpriteCommon* spriteCommon) {

	whiteSP = std::make_unique<Sprite>();
	whiteSP->Initialize(spriteCommon, 3);
	whiteSP->SetAnchorpoint({ 0.0f, 0.0f });
	whiteSP2 = std::make_unique<Sprite>();
	whiteSP2->Initialize(spriteCommon, 6);
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
		}
	}
}
void PlayerHP::OnHit() {
	hitFlag = true;
	afterHP -= 100;
}

void PlayerHP::Draw() {
	whiteSP2->Draw();
	whiteSP->Draw();
	
}