/*
* TitleScene.cpp
* タイトルシーン全体の処理
*/

#include "TitleScene.h"
#include "imgui.h"

void TitleScene::Initialize(DirectXCommon* dxCommon, SoundManager* soundManager, SpriteCommon* spriteCommon, ViewProjection* viewPro) {

	input_ = Input::GetInstance();
	dxCommon_ = dxCommon;
	viewProjection = viewPro;
	soundManager_ = soundManager;
	spriteCommon_ = spriteCommon;
	winApp_ = WinApp::GetInstance();
	imGui.Initialize(winApp_, dxCommon_);

	//効果音
	SE = SEManager::GetInstance();
	SE->Initialize(soundManager_);

}

void TitleScene::Finalize() {
	//imGui終了処理
	imGui.Finalize();
}


void TitleScene::Update() {

	//ビュープロジェクション
	viewProjection->SetEye(cameraPos);
	viewProjection->SetTarget({ 0,cameraPos.y - 10,0 });
	viewProjection->Update();

	//シーン遷移処理
	if (input_->TriggerKey(DIK_SPACE)) {
		BaseScene* scene = new GamePlayScene();
		BaseScene::GetSceneManager()->SetNextScene(scene);
	}

	//ゲーム終了
	if (input_->TriggerKey(DIK_ESCAPE)) {
		SetEndRequest(true);
	}

	//imGuiの更新
	imGui.Begin();
	ImGui::Text("TitleScene");
	ImGui::Text("MousePos : (%f,%f)", mousePos.x, mousePos.y);
	imGui.End();
}

void TitleScene::Draw() {
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon_->GetCommandList());


	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	//スプライト描画前処理
	spriteCommon_->PreDraw();
	////描画コマンドここから
	spriteCommon_->Update();
	//sprite->SetPosition(position);


	//スプライト描画後処理
	spriteCommon_->PostDraw();

	//imGuiの描画
	imGui.Draw();
}
