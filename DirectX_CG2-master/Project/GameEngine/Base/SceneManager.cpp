/*
* SceneManager.cpp
* それぞれのシーンの管理
*/

#include "SceneManager.h"

SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {
	scene_->Finalize();
	delete	scene_;
}

void SceneManager::Update(DirectXCommon* dxCommon, SoundManager* soundManager, SpriteCommon* spriteCommon, ViewProjection* viewPro) {

	//次シーンの予約があるなら
	if (nextScene_) {
		//旧シーン終了
		if (scene_) {
			scene_->Finalize();
			delete scene_;
		}

		//シーン切り替え
		scene_ = nextScene_;
		nextScene_ = nullptr;

		//シーンマネージャをセット
		scene_->SetSceneManager(this);

		//次シーンを初期化
		scene_->Initialize(dxCommon, soundManager, spriteCommon, viewPro);
	}

	//実行中シーンを更新する
	scene_->Update();
	if (scene_->GetEndRequest()) {
		endRequest_ = true;
	}
}

void SceneManager::Draw() {
	scene_->Draw();
}