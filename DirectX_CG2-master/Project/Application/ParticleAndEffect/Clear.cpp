#include "Clear.h"

void Clear::Initialize(SpriteCommon* spriteCommon) {

	clearSP = std::make_unique<Sprite>();
	clearSP->Initialize(spriteCommon, SpriteManager::Clear);
	clearSP->SetSize({ clearSP->GetSize().x,  clearSP->GetSize().y});
}

void Clear::Update() {

	if (isClear) {
		//イージング用のフレームを進める
		if (frame <= frameMax) {
			frame++;
		}
	}
	else {
		if (frame > 0) {
			frame--;
		}
	}

	clearSP->SetPosition({
		WinApp::window_width / 2 + (position.x - position.x * MyMath::easeOutCubic(frame / frameMax)),
		WinApp::window_height / 2,
		});
	clearSP->Update();
}

void Clear::OnFlag() {	//クリアしたら
	//スプライトを表示
	isClear = true;
}

void Clear::Draw() {

	clearSP->Draw();
}