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

  stageField_->SetViewProjection(*viewProjection);

	gameover = std::make_unique<Gameover>();
	gameover->Initialize(spriteCommon);

	clear = std::make_unique<Clear>();
	clear->Initialize(spriteCommon);

	ground = std::make_unique<Ground>();
	ground->Initialize(Model::LoadFromOBJ("Ground"));

	coral = std::make_unique<BackObject>();
	coral->Initialize(Model::LoadFromOBJ("Coral"), 30, 200, -20.0f);
	box = std::make_unique<BackObject>();
	box->Initialize(Model::LoadFromOBJ("WoodenBox"), 10, 100, -15.0f);

	skydome = std::make_unique<Skydome>();
	skydome->Initialize(Model::LoadFromOBJ("Skydome"));

	item_ = std::make_unique<Item>();
	item_->Initialize();

	bubble = std::make_unique<ParticleManager>();
	bubble->Initialize(Model::LoadFromOBJ("Particle"));

}

void GamePlayScene::Finalize() {
	//imGui終了処理
	imGui.Finalize();
}

void GamePlayScene::Update() {
  viewProjection->CameraMoveVector({ 0,0,0.0f });
	viewProjection->Update();

	//クリア処理
	if (bossEnemy_->GetHP() <= 0) {
		clear->OnFlag();

		if (input_->TriggerKey(DIK_SPACE)) {
			BaseScene* scene = new TitleScene();
			BaseScene::GetSceneManager()->SetNextScene(scene);
		}

    stageField_->Update();
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

	item_->Update(player->GetHP(), player->GetPosition());
	viewProjection->SetTarget(player->GetPosition());

	viewProjection->SetEye({
		player->GetPosition().x + cameraPosition.x,
		0,
		player->GetPosition().z + cameraPosition.z
		});

	//viewProjection->SetEye({0,0,-20});
	//viewProjection->SetTarget({0,0,0});

	viewProjection->Update();

	Collision();
	//ゲーム終了
	if (input_->TriggerKey(DIK_ESCAPE)) {
		SetEndRequest(true);
	}

	gameover->Update();
	clear->Update();

	//景観オブジェクト
	ground->Update(player->GetPosition());
	coral->Update(player->GetPosition());
	box->Update(player->GetPosition());
	skydome->Update(player->GetPosition());

	DirectX::XMFLOAT3 bubblePos = {
		MyMath::RandomFloat(player->GetPosition().x + 100.0f,player->GetPosition().x + 150.0f),
		MyMath::RandomFloat(player->GetPosition().y - 20.0f,player->GetPosition().y),
		MyMath::RandomFloat(player->GetPosition().z,player->GetPosition().z + 100.0f),
	};
	bubble->AddAlways(bubblePos, 2.0f, 300.0f,{1,1,1,0.51f});
	bubble->UpdateAlways(10, true, true);
	
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

    //for(auto& block : stageField_->GetList()) {
    //  block->Draw();
    //}

  //stageField_->Draw();
	
	bossEnemy_->Draw();
	player->Draw();

	ground->Draw();
	coral->Draw();
	box->Draw();
	skydome->Draw();
	bubble->Draw();
	
	item_->Draw();
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
		if (bossEnemy_->GetPosition().x - player->GetPosition().x < 5 &&
			-5 < bossEnemy_->GetPosition().x - player->GetPosition().x) {
			if (bossEnemy_->GetPosition().y - player->GetPosition().y < 5 &&
				-5 < bossEnemy_->GetPosition().y - player->GetPosition().y) {
				if (bossEnemy_->GetPosition().z - player->GetPosition().z < 15 &&
					-15 < bossEnemy_->GetPosition().z - player->GetPosition().z) {
					player->OnCollision(1);
					player->DodgeOnHit();
				}
			}
		}

		//if (item_->GetPosition().x - player->GetPosition().x < 5 &&
		//	-5 < item_->GetPosition().x - player->GetPosition().x) {
		//	if (item_->GetPosition().y - player->GetPosition().y < 2 &&
		//		-2 < item_->GetPosition().y - player->GetPosition().y) {
		//		if (item_->GetPosition().z - player->GetPosition().z < 2 &&
		//			-2 < item_->GetPosition().z - player->GetPosition().z) {
		//			if (item_->GetIsDamage() == true) {
		//				bossEnemy_->Damage(1);
		//			}
		//			else if (item_->GetIsHeel() == true) {
		//				//player->OnCollision(-1);
		//				player->ItemEffect(heal);
		//			}
		//			else if (item_->GetIsSlow() == true) {
		//				//player->DodgeOnHit();
		//			}
		//			item_->Ability(player->GetHP(), 1, player->GetPosition());
		//			//障害物と敵の当たり判定
		//			for (std::unique_ptr<Obstacle>& obs : obstacles) {
		//				const float x = (obs->GetPosition().x - item_->GetPosition().x) * (obs->GetPosition().x - item_->GetPosition().x);
		//				const float y = (obs->GetPosition().y - item_->GetPosition().y) * (obs->GetPosition().y - item_->GetPosition().y);
		//				const float r = (item_->GetScale().x + obs->GetScale()) * (item_->GetScale().x + obs->GetScale());

		//				if (x + y <= r) {
		//					item_->Ability(player->GetHP(), 1, player->GetPosition());
		//				}
		//			}
		//		}
		//	}
		//}
		if (input_->TriggerKey(DIK_A)) {
			for (int i = 0; i < 3; i++) {
				bossEnemy_->Damage();
			}
			
		}

		
}