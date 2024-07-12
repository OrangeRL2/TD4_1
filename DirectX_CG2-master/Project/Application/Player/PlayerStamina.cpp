#include "PlayerStamina.h"

void PlayerStamina::Initialize(SpriteCommon* spriteCommon) {

	whiteSP = std::make_unique<Sprite>();
	whiteSP->Initialize(spriteCommon, 4);
	whiteSP->SetAnchorpoint({ 0.0f, 0.0f });

	whiteSP2 = std::make_unique<Sprite>();
	whiteSP2->Initialize(spriteCommon, 5);
	whiteSP2->SetAnchorpoint({ 0.0f, 0.0f });
}

void PlayerStamina::Update(float playerStamina) {
	whiteSP2->SetPosition({ 100.0f,90.0f });
	whiteSP2->SetSize({ 600,12.0f });
	whiteSP->SetPosition({ 100.0f,90.0f });
	whiteSP->SetSize({ playerStamina,12.0f });
	//whiteSP->SetColor({ 0.5f,0.0f,0.0f,transTimer });
	whiteSP2->Update();
	whiteSP->Update();
	//HP -= 0.2f;
	if (useFlag == true) {
		if (stamina > afterStamina) {
			stamina -= 5.0f;
		}
		if (stamina < afterStamina) {
			stamina = afterStamina;
		}
		if (stamina == afterStamina) {
			useFlag = false;
		}
	}
	if (useFlag == false) {
		if (stamina < 500.0f) {
			stamina += 0.5f;
		}

		if (stamina >= 500.0f) {
			stamina = 500.0f;
		}
	}
}
void PlayerStamina::OnUse() {
	useFlag = true;
	if (afterStamina > 0.0f) {
		afterStamina -= 100;
	}
	if (afterStamina < 0.0f) {
		afterStamina = 0.0f;
	}
}

void PlayerStamina::Draw() {
	
	whiteSP->Draw();
	whiteSP2->Draw();
}