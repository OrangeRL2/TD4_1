#include "DamageEffect.h"

void DamageEffect::Initialize(SpriteCommon* spriteCommon) {

	whiteSP = std::make_unique<Sprite>();
	whiteSP->Initialize(spriteCommon, SpriteManager::white1x1);


}

void DamageEffect::Update() {

	if (transTimer > 0) {
		transTimer -= transTimerVal;
	}

	whiteSP->SetPosition({ WinApp::window_width / 2,WinApp::window_height / 2 });
	whiteSP->SetSize({ WinApp::window_width,WinApp::window_height });
	whiteSP->SetColor({healColor.x,healColor.y,healColor.z,transTimer });
	whiteSP->Update();
}

void DamageEffect::SetTimer(DirectX::XMFLOAT3 color) {
	transTimer = transTimerMax;
	healColor = color;
}

void DamageEffect::Draw() {
	whiteSP->Draw();
}