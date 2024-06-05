#include "DamageEffect.h"

void DamageEffect::Initialize(SpriteCommon* spriteCommon) {

	whiteSP = std::make_unique<Sprite>();
	whiteSP->Initialize(spriteCommon, 0);


}

void DamageEffect::Update() {

	if (transTimer > 0) {
		transTimer -= transTimerVal;
	}

	whiteSP->SetPosition({ WinApp::window_width / 2,WinApp::window_height / 2 });
	whiteSP->SetSize({ WinApp::window_width,WinApp::window_height });
	whiteSP->SetColor({ 0.5f,0.0f,0.0f,transTimer });
	whiteSP->Update();
}

void DamageEffect::SetTimer() {
	transTimer = transTimerMax;
}

void DamageEffect::Draw() {
	whiteSP->Draw();
}