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

	//シーン切り替え演出
	sceneChange = std::make_unique<SceneChange>();
	sceneChange->Initialize(spriteCommon_, false);

	pressSpace = std::make_unique<PressSpace>();
	pressSpace->Initialize(spriteCommon_);
	pressSpace->SetIsActive(true);

	//タイトルのスプライト
	titleSprite = std::make_unique<Sprite>();
	titleSprite->Initialize(spriteCommon_, SpriteManager::title);
	titleSprite->SetPosition({ WinApp::window_width / 2, 300 });

	ground = std::make_unique<Ground>();
	ground->Initialize(Model::LoadFromOBJ("Ground"));

	coral = std::make_unique<BackObject>();
	coral->Initialize(Model::LoadFromOBJ("Coral"), 30, 200, -20.0f);
	stone = std::make_unique<BackObject>();
	stone->Initialize(Model::LoadFromOBJ("Stone"), 10, 100, -15.0f);

	skydome = std::make_unique<Skydome>();
	skydome->Initialize(Model::LoadFromOBJ("Skydome"));

	bubble = std::make_unique<ParticleManager>();
	bubble->Initialize(Model::LoadFromOBJ("Particle"));

}

void TitleScene::Finalize() {
	//imGui終了処理
	imGui.Finalize();
}


void TitleScene::Update() {

	SE->PlayBGM(&BGM, 5.0f, 1.0f);

	cameraPos.x += 0.1f;

	//ビュープロジェクション
	viewProjection->SetEye(cameraPos);
	viewProjection->SetTarget({ cameraPos.x,cameraPos.y,0 });
	viewProjection->Update();

	pressSpace->Update();

	//シーン遷移処理
	if (input_->TriggerKey(DIK_SPACE) && !sceneChange->GetIsChange()) {
		sceneChange->SetIsReduction(true);
		SE->Play(SE->Decision(), 1.0f, 0.0f);
		SE->Stop(BGM);
	}

	if (sceneChange->GetCompleted()) {
		BaseScene* scene = new GamePlayScene();
		BaseScene::GetSceneManager()->SetNextScene(scene);
	}

	sceneChange->Update();
	//景観オブジェクト
	ground->Update({ cameraPos.x,cameraPos.y,0});
	coral->Update({ cameraPos.x,cameraPos.y,0 },0.0f);
	stone->Update({ cameraPos.x,cameraPos.y,0 },0.0f);
	skydome->Update({ cameraPos.x,cameraPos.y,0 });

	//UI

	DirectX::XMFLOAT3 bubblePos = {
		MyMath::RandomFloat(-100.0f,100.0f),
		MyMath::RandomFloat(-20.0f,0),
		MyMath::RandomFloat(0,100.0f),
	};
	bubble->AddAlways(bubblePos, 2.0f, 300.0f, { 1,1,1,0.51f });
	bubble->UpdateAlways(10, true, true);

	//ゲーム終了
	if (input_->TriggerKey(DIK_ESCAPE)) {
		SetEndRequest(true);
	}

	//imGuiの更新
	imGui.Begin();
	ImGui::Text("TitleScene");
	//ImGui::Text("MousePos : (%f,%f)", mousePos.x, mousePos.y);
	imGui.End();
}

void TitleScene::Draw() {
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon_->GetCommandList());

	ground->Draw();
	coral->Draw();
	stone->Draw();
	skydome->Draw();
	bubble->Draw();

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	//スプライト描画前処理
	spriteCommon_->PreDraw();
	////描画コマンドここから
	spriteCommon_->Update();

	titleSprite->Draw();
	pressSpace->Draw();
	sceneChange->Draw();
	//sprite->SetPosition(position);


	//スプライト描画後処理
	spriteCommon_->PostDraw();

	//imGuiの描画
	imGui.Draw();
}
