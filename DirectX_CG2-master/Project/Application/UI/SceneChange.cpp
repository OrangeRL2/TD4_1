#include "SceneChange.h"
#include "MyMath.h"

void SceneChange::Initialize(SpriteCommon* spriteCommon, const bool first) {

	//スプライト初期化
	for (std::unique_ptr<Sprite>& sp : SP) {

		sp = std::make_unique<Sprite>();
		sp->Initialize(spriteCommon, SpriteManager::sceneChange);
		sp->SetTextureSize({ 1,1 });
	}

	SP[0]->SetTextureSize({ textureSize, textureSize });
	SP[0]->SetLeftTop({ 0, 0 });

	//座標設定
	SP[0]->SetPosition({ WinApp::window_width / 2,WinApp::window_height / 2 });
	SP[1]->SetPosition({ WinApp::window_width / 2,0 });
	SP[2]->SetPosition({ WinApp::window_width / 2,WinApp::window_height });
	SP[3]->SetPosition({ 0,WinApp::window_height / 2 });
	SP[4]->SetPosition({ WinApp::window_width,WinApp::window_height / 2 });

	//アンカーポイント
	SP[0]->SetAnchorpoint({ 0.5f,0.5f });
	SP[1]->SetAnchorpoint({ 0.5f,0.0f });
	SP[2]->SetAnchorpoint({ 0.5f,1.0f });
	SP[3]->SetAnchorpoint({ 0.0f,0.5f });
	SP[4]->SetAnchorpoint({ 1.0f,0.5f });

	if (first) {
		frame = MaxFrame;
	}
	else {
		frame = 0.0f;
	}
}

void SceneChange::Update() {

	//サイズを変更
	if (isReduction && frame > 0) {
		frame--;
	}
	if (!isReduction && frame < MaxFrame) {
		frame++;
	}
	size = MyMath::easeInCubic(frame / MaxFrame) * MaxSize;

	//待機時間
	if (size <= 0) {
		waitTime--;

		if (waitTime <= 0) {
			waitTime = MaxWaitTime;
			isCompleted = true;
		}
	}

	//シーン遷移中か
	if (frame < MaxFrame) {
		isChange = true;
	}
	else {
		isChange = false;
	}

	SP[0]->SetSize({ size, size });
	SP[1]->SetSize({ WinApp::window_width,WinApp::window_height / 2 - size / 2});
	SP[2]->SetSize({ WinApp::window_width,WinApp::window_height / 2 - size / 2 + 1});
	SP[3]->SetSize({ WinApp::window_width / 2 - size / 2,WinApp::window_height});
	SP[4]->SetSize({ WinApp::window_width / 2 - size / 2,WinApp::window_height});

	for (std::unique_ptr<Sprite>& sp : SP) {
		sp->Update();
	}
}

void SceneChange::Draw() {
	for (std::unique_ptr<Sprite>& sp : SP) {

		if (frame < MaxFrame) {
			sp->Draw();
		}
	}
}
