/*
* MyGame.cpp
* ゲーム全体の処理
*/

#include "MyGame.h"

void MyGame::Initialize() {

	//基底クラスの初期化処理
	Framewark::Initialize();

	//シーンの生成と初期化
	scene_ = new TitleScene();
	//シーンマネージャに最初のシーンをセット
	Framewark::GetSceneManager()->SetNextScene(scene_);

}

void MyGame::Finalize() {

	//基底クラスの終了処理
	Framewark::Finalize();
}

void MyGame::Update() {

	//基底クラスの更新処理
	Framewark::Update();

}

void MyGame::Draw() {

	//描画前処理
	Framewark::GetDxCommon()->PreDraw();

	//Object3d::PreDraw(Framewark::GetDxCommon()->GetCommandList());

	//Object3d::PostDraw();

	Framewark::GetSceneManager()->Draw();
	//postEffect->Draw(spriteCommon);

	//描画後処理
	Framewark::GetDxCommon()->PostDraw();
}