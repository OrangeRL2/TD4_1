/*
* GamePlayScene.cpp
* ゲームプレイシーン全体の処理
*/

#include "GamePlayScene.h"
#include "MyMath.h"
#include "imgui.h"

void GamePlayScene::Initialize(DirectXCommon* dxCommon, SoundManager* soundManager, SpriteCommon* spriteCommon, ViewProjection* viewPro) {
	
	viewProjection = viewPro;
	soundManager_ = soundManager;
	spriteCommon_ = spriteCommon;
	dxCommon_ = dxCommon;
	input_ = Input::GetInstance();
	winApp_ = WinApp::GetInstance();

	imGui.Initialize(winApp_, dxCommon_);

	SE = SEManager::GetInstance();
	SE->Initialize(soundManager_);

	bossEnemy_ = std::make_unique<BossEnemy>();
	bossEnemy_->Initialize();

	player = std::make_unique<Player>();
	player->Initialize(spriteCommon, viewProjection);

}

void GamePlayScene::Finalize() {
	//imGui終了処理
	imGui.Finalize();
}

void GamePlayScene::Update() {

	viewProjection->Update();
	
	//シーン遷移処理
	if (input_->TriggerKey(DIK_SPACE)) {
		BaseScene* scene = new TitleScene();
		BaseScene::GetSceneManager()->SetNextScene(scene);
	}

	bossEnemy_->Update();

	player->Update();
	viewProjection->SetTarget(player->GetPosition());
	viewProjection->SetEye({
		player->GetPosition().x + cameraPosition.x,
		player->GetPosition().y,
		player->GetPosition().z + cameraPosition.z
		});
	viewProjection->Update();
	//ゲーム終了
	if (input_->TriggerKey(DIK_ESCAPE)) {
		SetEndRequest(true);
	}

	//imGuiの更新
	imGui.Begin();
	ImGui::Text("GameScene");
	ImGui::Text("test");
	imGui.End();
}


void GamePlayScene::Draw() {
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon_->GetCommandList());

	bossEnemy_->Draw();
	player->Draw();
	
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	//スプライト描画前処理
	spriteCommon_->PreDraw();
	spriteCommon_->Update();
	//スプライト描画後処理
	spriteCommon_->PostDraw();

	//imGuiの描画
	imGui.Draw();

}
