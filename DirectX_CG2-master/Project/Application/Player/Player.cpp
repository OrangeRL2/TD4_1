/*
* Player.cpp
* 自機の処理
*/

#include "Player.h"
#include "MyMath.h"
#include <cmath>
#include <random>

void Player::Initialize(SpriteCommon* spCommon, ViewProjection* viewPro) {
	input_ = Input::GetInstance();
	viewProjection = viewPro;
	spriteCommon_ = spCommon;
	scale = { 1.0f,1.0f,1.0f };
	model_ = Model::LoadFromOBJ("WoodenBox");;
	playerObject = std::make_unique<Object3d>();
	playerObject->Initialize();
	playerObject->SetModel(model_);
	playerObject->SetPosition(position);
	playerObject->SetScale(scale);

}

void Player::Update() {

	if (input_->PushKey(DIK_W)) {
		position.x += 1.0f;
	}
	else if (input_->PushKey(DIK_D)) {
		position.y += 1.0f;
	}
	else if (input_->PushKey(DIK_S)) {
		position.x -= 1.0f;
	}
	else if (input_->PushKey(DIK_A)) {
		position.y -= 1.0f;
	}

	if (input_->PushKey(DIK_P)) {
		scale.x += 1.0f;
		scale.y += 1.0f;
		scale.z += 1.0f;
	}

	if (input_->PushKey(DIK_O)) {
		scale.x -= 1.0f;
		scale.y -= 1.0f;
		scale.z -= 1.0f;
	}

	playerObject->SetPosition(position);

	playerObject->Update();
}

void Player::Draw() {
	//オブジェクト描画
	playerObject->Draw();
}