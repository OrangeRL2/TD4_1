/*
* BossEnemy.cpp
* ボスの挙動
*/

#include "BossEnemy.h"

#include "Input.h"

void BossEnemy::Initialize()
{
	// ===== ボスの生成 ===== //
	bossEnemyModel_ = Model::LoadFromOBJ("Box");
	bossEnemyObj_ = Object3d::Create();
	bossEnemyObj_->SetModel(bossEnemyModel_);
	bossEnemyObj_->SetPosition(position_);
	bossEnemyObj_->SetScale(scale_);
	bossEnemyObj_->SetRotation(rotation_);
}

void BossEnemy::Update(const DirectX::XMFLOAT3& distance)
{
	// ボスの攻撃
	BossEnemy::Attack(distance);

	// ボスの挙動
	BossEnemy::Move();
	
	// ===== ボスの更新 ===== //
	bossEnemyObj_->Update();
}

void BossEnemy::Draw()
{
	// ===== ボスの描画 ===== //
	bossEnemyObj_->Draw();
}

void BossEnemy::Attack(const DirectX::XMFLOAT3& distance)
{
	// ボスの攻撃の発動条件
	if (++time_ >= 100) {
		isAttack_ = true;
		time_ = 0;
	}
	if (isAttack_ == true) {
		attackTimer_++;
		speed_ += 0.1f;
	}
	if (attackTimer_ >= 10) {
		isAttack_ = false;
		attackTimer_ = 0;
		speed_ = speedAddition_;
	}
	if ((distance.x - 10) <= position_.x) {
		position_.x -= 0.1f;
	}
}

void BossEnemy::Move()
{
	// ===== ボスの移動 ===== //
	move_.x = speed_ + speedBoost_;
	if (speed_ > speedLim_) {
		speed_ = speedLim_;
		speedAddition_ = speedLim_;
	}
	if (speed_ < speedLim_) {
		speed_ += 0.001f;
		speedAddition_ += 0.001f;
	}
	if (OogamiEngine::Input::GetInstance()->PushKey(DIK_D)) {
		position_.y += gravity_;
	} else if (position_.y >= -moveLim_) {
		position_.y -= gravity_;
	}
	
	position_.x += move_.x;
	position_.y += move_.y;
	position_.z += move_.z;
	bossEnemyObj_->SetPosition(position_);
	bossEnemyObj_->SetRotation(rotation_);
}
