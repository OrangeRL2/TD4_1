/*
* FrameWark.cpp
* ゲームの枠組み
*/

#include "Framewark.h"
#include "ObjectLoader.h"

void Framewark::Initialize() {
	//WindowsAPIの初期化
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	//入力の初期化
	input = Input::GetInstance();
	input->Initialize(winApp);

	//DirectXの初期化
	dxCommon_ = new DirectXCommon();
	dxCommon_->Initialize(winApp);

	//3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon_->GetDevice());

  //モデルローダー内でモデルを生成
  ObjectLoader::GetInstance()->CreateModelList();
  ObjectLoader::GetInstance()->CreateObjectList();

	//FBXローダーの初期化
	FbxLoader::GetInstance()->Initialize(dxCommon_->GetDevice());

	spriteCommon_ = new SpriteCommon();
	spriteCommon_->Initialize(dxCommon_);

	SPManager = new SpriteManager();
	SPManager->Initialize(spriteCommon_);

	//サウンドマネージャー初期化
	soundManager_ = new SoundManager();
	soundManager_->Initialize();

	//ビュープロジェクション
	viewProjection = new ViewProjection();
	viewProjection->Initialize(Framewark::GetWinApp()->window_width, Framewark::GetWinApp()->window_height);
	viewProjection->SetTarget({ 0,0,0 });

	//シーンマネージャの生成
	sceneManager_ = new SceneManager();

	////ポストエフェクト
	//PostEffect* postEffect = nullptr;
	////ポストエフェクト用のテクスチャ読み込み
	////spriteCommon->LoadTexture(100, "Resource/white1x1.png");
	////ポストエフェクトの初期化
	//postEffect = new PostEffect();
	//postEffect->Initialize(dxCommon);
}

void Framewark::Finalize() {

	//シーンマネージャの解放
	delete sceneManager_;
	delete viewProjection;
	delete soundManager_;
	delete spriteCommon_;

	//WindowsAPIの終了処理
	winApp->Finalize();

	//delete postEffect;
	winApp->ScreenMode(false);

	//FBXローダーの解放処理
	FbxLoader::GetInstance()->Finalize();
	//DirectX解放
	delete dxCommon_;

}

void Framewark::Update() {

	winApp->Update();
	input->Update();

	sceneManager_->Update(dxCommon_, soundManager_, spriteCommon_, viewProjection);

	//キー入力でフルスクリーンを切り替え
	if (input->TriggerKey(DIK_F11)) {

		winApp->ScreenMode(fullScreen);

		if (fullScreen) {
			fullScreen = false;
		}
		else {
			fullScreen = true;
		}
	}
	if (winApp->ProcessMesseage() || sceneManager_->GetEndReques()) {
		endRequst_ = true;
	}
}

void Framewark::Draw() {
	sceneManager_->Draw();
}

void Framewark::Run() {

	//ゲームの初期化
	Initialize();

	while (true) {	//ゲームループ

		//毎フレーム更新
		Update();
		//終了リクエストが来たら抜ける
		if (IsEndRequst()) {
			break;
		}

		//描画
		Draw();
	}

	//ゲームの終了
	Finalize();
}
