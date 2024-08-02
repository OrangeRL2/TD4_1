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

	player = std::make_unique<Player>();
	player->Initialize(spriteCommon, viewProjection, SE);
	player->Update();
	player->Update();
	
	obsModel = Model::LoadFromOBJ("obstacle");

	stageField_->SetViewProjection(*viewProjection);

	gameover = std::make_unique<Gameover>();
	gameover->Initialize(spriteCommon);

	clear = std::make_unique<Clear>();
	clear->Initialize(spriteCommon);

	ground = std::make_unique<Ground>();
	ground->Initialize(Model::LoadFromOBJ("Ground"));

	coral = std::make_unique<BackObject>();
	coral->Initialize(Model::LoadFromOBJ("Coral"), 30, 150, -30.0f);
	coral->SetColor({ 1,0.5f,1,1 });

	stone = std::make_unique<BackObject>();
	stone->Initialize(Model::LoadFromOBJ("Stone"), 20, 100, -20.0f);

	seaweed = std::make_unique<BackObject>();
	seaweed->Initialize(Model::LoadFromOBJ("Seaweed"), 5, 100, -20.0f);

	skydome = std::make_unique<Skydome>();
	skydome->Initialize(Model::LoadFromOBJ("Skydome"));

	item_ = std::make_unique<Item>();
	item_->Initialize();

	bubble = std::make_unique<ParticleManager>();
	bubble->Initialize(Model::LoadFromOBJ("Particle"));
	destParticle = std::make_unique<ParticleManager>();
	destParticle->Initialize(Model::LoadFromOBJ("Particle"));
	hitParticle = std::make_unique<ParticleManager>();
	hitParticle->Initialize(Model::LoadFromOBJ("Particle"));

	bossHPSprite = std::make_unique<Sprite>();
	bossHPSprite->Initialize(spriteCommon_, SpriteManager::white1x1);
	bossHPSprite->SetAnchorpoint({ 0,0 });
	bossHPSprite->SetPosition({ WinApp::window_width / 2 - 200, WinApp::window_height - 100 });
	bossHPSprite->SetColor({ 0,1,0.5f,1 });

	bossSprite = std::make_unique<Sprite>();
	bossSprite->Initialize(spriteCommon_, SpriteManager::Boss);
	bossSprite->SetPosition({ WinApp::window_width / 2 - 300, WinApp::window_height - 80 });
	bossSprite->SetSize({ bossSprite->GetSize().x / 3,bossSprite->GetSize().y / 3});

	pauseSprite = std::make_unique<Sprite>();
	pauseSprite->Initialize(spriteCommon_, SpriteManager::Pause);
	pauseSprite->SetPosition({ WinApp::window_width / 2, WinApp::window_height / 2 });

	tutorialSprite = std::make_unique<Sprite>();
	tutorialSprite->Initialize(spriteCommon_, SpriteManager::Tutorial);
	tutorialSprite->SetPosition({ WinApp::window_width / 2, WinApp::window_height / 3 });
	tutorialSprite->SetSize({ tutorialSprite->GetSize().x * 1.5f, tutorialSprite->GetSize().y * 1.5f });

	//シーン切り替え演出
	sceneChange = std::make_unique<SceneChange>();
	sceneChange->Initialize(spriteCommon_, false);

	pressSpace = std::make_unique<PressSpace>();
	pressSpace->Initialize(spriteCommon_);
	pressSpace->SetIsActive(true);

}

void GamePlayScene::Finalize() {
	//imGui終了処理
	imGui.Finalize();
}

void GamePlayScene::Update() {

	//障害物の更新
	if (obsInterval < 0) {
		std::unique_ptr<Obstacle>obs = std::make_unique<Obstacle>();

		//出現場所ランダム化
		DirectX::XMFLOAT3 pos = {
			player->GetPosition().x + 50,
			MyMath::RandomFloat(-15,15),
			0
		};
		obs->Initialize(obsModel, pos);
		obstacles.push_back(std::move(obs));
		obsInterval = obsIntervalMax;
	}

	for (std::unique_ptr<Obstacle>& obs : obstacles) {
		obs->Update();
	}
	obstacles.remove_if([](std::unique_ptr<Obstacle>& obs) {
		return obs->GetIsDead();
		});

	viewProjection->CameraMoveVector({ 0,0,0.0f });
	viewProjection->Update();

	//ループ音声
	SE->PlayBGM(&BGM, 5.0f, 1.0f);

	if (!isPause && !isTutorial) {
		if (isObsActive) {
			obsInterval--;
		}

		item_->Update(player->GetHP(), player->GetPosition());
		player->Update();
		player->Update();
		bossEnemy_->Update(player->GetPosition());
		bossEnemy_->Update(player->GetPosition());

		DirectX::XMFLOAT3 bubblePos = {
		MyMath::RandomFloat(player->GetPosition().x - 50,player->GetPosition().x + 50.0f),
		MyMath::RandomFloat(player->GetPosition().y - 20.0f,player->GetPosition().y),
		MyMath::RandomFloat(player->GetPosition().z,player->GetPosition().z + 100.0f),
		};
		bubble->AddAlways(bubblePos, 2.0f, 300.0f, { 1,1,1,0.51f });
		bubble->UpdateAlways(10, true, true);

	}

	destParticle->UpdateSpin(bossEnemy_->GetPosition(), 1.0f);
	hitParticle->UpdateSpin(bossEnemy_->GetPosition(), 1.0f);

	if (input_->TriggerKey(DIK_Q)) {
		if (isPause) {
			isPause = false;
		}
		else {
			isPause = true;
		}
	}
	//HP0でゲームオーバー
	if (player->GetHP() <= 0) {
		gameover->OnFlag();
		pressSpace->SetIsActive(true);

		if (input_->TriggerKey(DIK_SPACE)) {
			sceneChange->SetIsReduction(true);
			SE->Play(SE->Decision(), 1.0f, 0.0f);
			SE->Stop(BGM);
		}
	}
	//クリア処理
	if (bossEnemy_->GetHP() <= 0) {
		clear->OnFlag();
		pressSpace->SetIsActive(true);

		if (input_->TriggerKey(DIK_SPACE)) {
			sceneChange->SetIsReduction(true);
			SE->Play(SE->Decision(), 1.0f, 0.0f);
			SE->Stop(BGM);
		}

		isObsActive = false;
	}
	else {
		isObsActive = true;
	}

	stageField_->Update();

	viewProjection->SetTarget({
		player->GetPosition().x,
		0,
		player->GetPosition().z,
		});

	//viewProjection->SetTarget(player->GetPosition());

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

	//シーン切り替え
	sceneChange->Update();
	if (sceneChange->GetCompleted()) {
		BaseScene* scene = new TitleScene();
		BaseScene::GetSceneManager()->SetNextScene(scene);
	}

	//景観オブジェクト
	ground->Update(player->GetPosition());
	coral->Update(player->GetPosition(), 0.0f);
	stone->Update(player->GetPosition(), 0.0f);
	seaweed->Update(player->GetPosition(), 180.0f * MyMath::RandomInt(0, 1));
	skydome->Update(player->GetPosition());

	bossHPSprite->SetSize({ (float)bossEnemy_->GetHP() * 50, 30.0f });

	//チュートリアルの処理
	if (isTutorial) {
		pressSpace->SetIsActive(true);
		if (input_->TriggerKey(DIK_SPACE)) {
			isTutorial = false;
			pressSpace->SetIsActive(false);
		}
	}

	pressSpace->Update();

	//imGuiの更新
	imGui.Begin();
	ImGui::Text("GameScene");
	ImGui::Text("test");
	ImGui::Text("player pos y %f", player->GetPosition().y);
	ImGui::Text("enemy pos y %f", bossEnemy_->GetPosition().y);
	ImGui::Text("hp %d", player->GetHP());
	ImGui::Text("boss hp %d", bossEnemy_->GetHP());
	ImGui::Text("move %d", player->GetMove());
	imGui.End();
}


void GamePlayScene::Draw() {
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon_->GetCommandList());

	//for(auto& block : stageField_->GetList()) {
	//  block->Draw();
	//}

  //stageField_->Draw();

	if (!isPause && !isTutorial) {
		bossEnemy_->Draw();
		player->Draw();
	}

	bossEnemy_->Draw();
	player->Draw();


	ground->Draw();
	coral->Draw();
	stone->Draw();
	seaweed->Draw();
	skydome->Draw();
	bubble->Draw();
	destParticle->Draw();

	for (std::unique_ptr<Obstacle>& obs : obstacles) {
		obs->Draw();
	}

	item_->Draw();
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	//スプライト描画前処理
	spriteCommon_->PreDraw();
	spriteCommon_->Update();

	if (isPause) {
		pauseSprite->Draw();
	}
	else if (isTutorial) {
		tutorialSprite->Draw();
	}

	bossSprite->Draw();
	bossHPSprite->Draw();
	pressSpace->Draw();
	gameover->Draw();
	clear->Draw();
	player->Draw2D();
	sceneChange->Draw();

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


		if (item_->GetPosition().x - player->GetPosition().x < 5 &&
			-5 < item_->GetPosition().x - player->GetPosition().x) {
			if (item_->GetPosition().y - player->GetPosition().y < 5 &&
				-5 < item_->GetPosition().y - player->GetPosition().y) {
				if (item_->GetPosition().z - player->GetPosition().z < 2 &&
					-2 < item_->GetPosition().z - player->GetPosition().z) {
					if (item_->GetIsDamage() == true) {
						bossEnemy_->Damage(1);

						if (bossEnemy_->GetHP() <= 0) {
							destParticle->AddSpin(bossEnemy_->GetPosition(), 2, 60, 30, 20, true);
						}
					}
					else if (item_->GetIsHeel() == true) {
						player->OnCollision(-1);
					}
					else if (item_->GetIsSlow() == true) {
						//player->DodgeOnHit();
					}
					item_->Ability(player->GetHP(), 1, player->GetPosition());

				}
				else if (item_->GetIsSlow() == true) {
					//player->DodgeOnHit();
				}
				item_->Ability(player->GetHP(), 1, player->GetPosition());
			}
		}
	}

	//障害物と自機の当たり判定
	for (std::unique_ptr<Obstacle>& obs : obstacles) {
		const float x = (obs->GetPosition().x - player->GetPosition().x) * (obs->GetPosition().x - player->GetPosition().x);
		const float y = (obs->GetPosition().y - player->GetPosition().y) * (obs->GetPosition().y - player->GetPosition().y);
		const float r = (player->GetScale().x + obs->GetScale()) * (player->GetScale().x + obs->GetScale());

		if (x + y <= r) {


				if (player->GetEaseingFlag() && !obs->GetIsCounter()) {
					obs->Counter();
					SE->Play(SE->Counter(), 1.0f, 0.0f);
					destParticle->AddSpin(obs->GetPosition(), 1, 20, 5, 10, false);
				}
				else {

					if (!obs->GetIsCounter() && isObsActive) {
						if (player->GetHP() > 0) {
							player->OnCollision(1);
							obs->Dead();
						}
					}

				}
			}
		}
	}

	//障害物と敵の当たり判定
	for (std::unique_ptr<Obstacle>& obs : obstacles) {
		const float x = (obs->GetPosition().x - bossEnemy_->GetPosition().x) * (obs->GetPosition().x - bossEnemy_->GetPosition().x);
		const float y = (obs->GetPosition().y - bossEnemy_->GetPosition().y) * (obs->GetPosition().y - bossEnemy_->GetPosition().y);
		const float r = (bossEnemy_->GetScale().x + obs->GetScale()) * (bossEnemy_->GetScale().x + obs->GetScale());

		if (x + y <= r) {


				if (obs->GetIsCounter()) {
					obs->Dead();
					bossEnemy_->Damage(1);
					SE->Play(SE->Hit(),1.0f,0.0f);
					if (bossEnemy_->GetHP() <= 0) {
						destParticle->AddSpin(bossEnemy_->GetPosition(), 2, 60, 30, 20, true);
					}
				}

			}
		}
	}
}