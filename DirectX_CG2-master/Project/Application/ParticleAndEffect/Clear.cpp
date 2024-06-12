#include "Clear.h"

void Clear::Initialize(SpriteCommon* spriteCommon) {

	clearSP = std::make_unique<Sprite>();
	clearSP->Initialize(spriteCommon, 2);
	clearSP->SetSize({ clearSP->GetSize().x * 2,  clearSP->GetSize().y * 2 });
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
	if (isClear) {
		isClear = false;
	}
	else {
		isClear = true;
	}
}

void Clear::Draw() {

	clearSP->Draw();
}