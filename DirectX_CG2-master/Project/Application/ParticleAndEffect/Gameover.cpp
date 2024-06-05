#include "Gameover.h"

void Gameover::Initialize(SpriteCommon* spriteCommon) {

	gameoverSP = std::make_unique<Sprite>();
	gameoverSP->Initialize(spriteCommon, 1);
}

void Gameover::Update() {

	if (isDraw) {
		//イージング用のフレームを進める
		if (frame <= frameMax) {
			frame++;
		}
	}

	gameoverSP->SetPosition({
		WinApp::window_width / 2,
		WinApp::window_height / 2 + (position.y - position.y * MyMath::easeOutCubic(frame / frameMax)),
		});
	gameoverSP->Update();
}

void Gameover::OnFlag() {	//ゲームオーバーになったら
	//スプライトを表示
	isDraw = true;
}

void Gameover::Draw() {

	if (isDraw) {
		gameoverSP->Draw();
	}
}