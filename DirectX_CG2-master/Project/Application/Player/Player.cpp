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
	playerObject->SetRotation(rot);
	speed = 0.0f;
}

void Player::Update() {
	//速度を決まる
	move.x = speed + speedBoost;
	rot.z = turnSpeed;
	//speedがspeedLimにならないように
	if (speed > speedLim) {
		speed = speedLim;
	}
	if (speed < speedLim)
	{
		speed += 0.001f;
	}
	//動き
	if (input_->PushKey(DIK_D)) {
		if (turnSpeed < 10.0f)
		{
			turnSpeed += 1.0f;
		}
		position.y += gravity;
	}
	//上に泳いでない時に下に動く
	else if (position.y >= -moveLim) {
		if (turnSpeed > -10.0f)
		{
			turnSpeed -= 1.0f;
		}
		position.y -= gravity;
	}
	//ローテーションを元に戻す
	if (turnSpeed <= 0.00f) {
		turnSpeed += 0.5f;
	}
	if (turnSpeed >= 0.0f) {
		turnSpeed -= 0.5f;

	}
	//無敵時間を減らす
	if (isInvincible) {
		invincibleTimer -= 5.0f;
		speed = 0.1f;
	}
	if (invincibleTimer <= 0) {
		invincibleTimer = invincibleTimerMax;
		isInvincible = false;
		
	}

	if (input_->PushKey(DIK_P)) {
		OnCollision(1);
	}

	position.x += move.x;
	position.y += move.y;
	position.z += move.z;
	playerObject->SetRotation(rot);
	playerObject->SetPosition(position);
	playerObject->Update();
}

void Player::OnCollision(const int dmg) {

	isHit = true;
	//無敵時間以外ならダメージ
	if (!isInvincible) {
		//const float n = 512.0f;

		hp -= dmg;
		isInvincible = true;
	}
}

void Player::Draw() {
	//オブジェクト描画
	if ((int)invincibleTimer % 2 == 0) {
		playerObject->Draw();
	}
}