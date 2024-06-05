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

  stageField_ =
    std::make_unique<StageField>();

  stageField_->Initialize();
	bossEnemy_ = std::make_unique<BossEnemy>();
	bossEnemy_->Initialize();

	spriteCommon->LoadTexture(0, "white1x1.png");
	spriteCommon->LoadTexture(1, "GameOver.png");
	spriteCommon->LoadTexture(2, "Clear.png");

	player = std::make_unique<Player>();
	player->Initialize(spriteCommon, viewProjection);


	gameover = std::make_unique<Gameover>();
	gameover->Initialize(spriteCommon);

	clear = std::make_unique<Clear>();
	clear->Initialize(spriteCommon);

	item_ = std::make_unique<Item>();
	item_->Initialize();

}

void GamePlayScene::Finalize() {
	//imGui終了処理
	imGui.Finalize();
}

void GamePlayScene::Update() {

  stageField_->Update();

	viewProjection->Update();
	
	//クリア処理
	if (bossEnemy_->GetHP() <= 0) {
		clear->OnFlag();

		if (input_->TriggerKey(DIK_SPACE)) {
			BaseScene* scene = new TitleScene();
			BaseScene::GetSceneManager()->SetNextScene(scene);
		}
	}

	bossEnemy_->Update(player->GetPosition());

	player->Update();
	//HP0でゲームオーバー
	if (player->GetHP() <= 0) {
		gameover->OnFlag();

		if (input_->TriggerKey(DIK_SPACE)) {
			BaseScene* scene = new TitleScene();
			BaseScene::GetSceneManager()->SetNextScene(scene);
		}
	}

	viewProjection->SetTarget({
		player->GetPosition().x,
		0,
		player->GetPosition().z,
		});


	player->Update();
	bossEnemy_->Update(player->GetPosition());
	item_->Update(player->GetPosition());
	viewProjection->SetTarget({ 
		player->GetPosition().x,
		0,
		player->GetPosition().x,
		});

	viewProjection->SetEye({
		player->GetPosition().x + cameraPosition.x,
		0,
		player->GetPosition().z + cameraPosition.z
		});

	viewProjection->Update();

	Collision();
	//ゲーム終了
	if (input_->TriggerKey(DIK_ESCAPE)) {
		SetEndRequest(true);
	}

	gameover->Update();
	clear->Update();

	
	//imGuiの更新
	imGui.Begin();
	ImGui::Text("GameScene");
	ImGui::Text("test");
	ImGui::Text("player pos y %f",player->GetPosition().y);
	ImGui::Text("enemy pos y %f",bossEnemy_->GetPosition().y);
	ImGui::Text("hp %d",player->GetHP());
	ImGui::Text("boss hp %d",bossEnemy_->GetHP());
	imGui.End();
}


void GamePlayScene::Draw() {
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon_->GetCommandList());

  stageField_->Draw();
	
	bossEnemy_->Draw();
	player->Draw();
	//item_->Draw();
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	//スプライト描画前処理
	spriteCommon_->PreDraw();
	spriteCommon_->Update();

	gameover->Draw();
	clear->Draw();
	player->Draw2D();

	//スプライト描画後処理
	spriteCommon_->PostDraw();

	//imGuiの描画
	imGui.Draw();

}

void GamePlayScene::Collision() {
		if (bossEnemy_->GetPosition().x - player->GetPosition().x < 7 &&
			-7 < bossEnemy_->GetPosition().x - player->GetPosition().x) {
			if (bossEnemy_->GetPosition().y - player->GetPosition().y < 5 &&
				-5 < bossEnemy_->GetPosition().y - player->GetPosition().y) {
				if (bossEnemy_->GetPosition().z - player->GetPosition().z < 2 &&
					-2 < bossEnemy_->GetPosition().z - player->GetPosition().z) {
					player->OnCollision(1);
				}
			}
		}

		if (item_->GetPosition().x - player->GetPosition().x < 5 &&
			-5 < item_->GetPosition().x - player->GetPosition().x) {
			if (item_->GetPosition().y - player->GetPosition().y < 5 &&
				-5 < item_->GetPosition().y - player->GetPosition().y) {
				if (item_->GetPosition().z - player->GetPosition().z < 2 &&
					-2 < item_->GetPosition().z - player->GetPosition().z) {
					//bossEnemy_->Damage();
				}
			}
		}
		if (input_->TriggerKey(DIK_A)) {
			bossEnemy_->Damage();
		}

		
}