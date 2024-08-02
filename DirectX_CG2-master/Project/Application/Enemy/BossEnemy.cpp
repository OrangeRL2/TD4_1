/*
* BossEnemy.cpp
* ボスの挙動
*/

#include "BossEnemy.h"

#include "Input.h"

void BossEnemy::Initialize()
{
	// ===== ボスの生成 ===== //
	bossEnemyModel_ = Model::LoadFromOBJ("Boss");
	bossEnemyObj_ = Object3d::Create();
	bossEnemyObj_->SetModel(bossEnemyModel_);
	bossEnemyObj_->SetPosition(position_);
	bossEnemyObj_->SetScale(scale_);
	bossEnemyObj_->SetRotation(rotation_);

	bossStatus.hp = 5;
}

void BossEnemy::Update(const DirectX::XMFLOAT3& playerPosition)
{
	// ボスの攻撃
	BossEnemy::Attack(playerPosition);

	// ボスの挙動
	BossEnemy::Move();

	// ボスの攻撃
	BossEnemy::SpinAttack();
	
	// ===== ボスの更新 ===== //

	if (color >= 1.0f) {
		color-=0.2f;
	}
	bossEnemyObj_->SetColor({ color,1.0f,1.0f,0.75f });

	position_ = {
		playerPosition.x - 20,
		0,
		0,
	};
	bossEnemyObj_->SetPosition(position_);
	bossEnemyObj_->Update();
}

void BossEnemy::Draw()
{
	// ===== ボスの描画 ===== //
	if (bossStatus.hp > 0) {
		bossEnemyObj_->Draw();
	}
}

void BossEnemy::Attack(const DirectX::XMFLOAT3& playerPosition)
{
	// ボスの攻撃の発動条件
	if (++time_ >= attackCoolTime_) {
		isAttack_ = true;
		time_ = 0;
	}
	if (isAttack_ == true) {
		attackTimer_++;
		speed_ += 0.1f;

		if (attackTimer_ >= 10) {
			isAttack_ = false;
			attackTimer_ = 0;
			speed_ = speedAddition_;
		}
	}

	// 攻撃を行った後元の位置に戻す
	float distance_ = playerPosition.x - playerDifference_;
	if (distance_ <= position_.x) {
		position_.x -= 0.1f;
	}
}

void BossEnemy::Move()
{
	// ===== ボスの移動 ===== //
	move_.x = speed_ + speedBoost_;
	if (speed_ > speedLim_) {
		speed_ = speedLim_;
	}
	if (speedAddition_ > speedLim_) {
		speedAddition_ = speedLim_;
	}
	if (speed_ < speedLim_) {
		speed_ += 0.001f;
	}
	if (speedAddition_ < speedLim_) {
		speedAddition_ += 0.001f;
	}
	
	position_.x += move_.x;
	position_.y += move_.y;
	position_.z += move_.z;
	bossEnemyObj_->SetPosition(position_);
	bossEnemyObj_->SetRotation(rotation_);

}

void BossEnemy::Damage(int damage_)
{
	// ボスのdethダメージ
	const int deathHp_ = 0;
	color = 10.0f;
	if (bossStatus.hp > deathHp_) {
		bossStatus.hp -= damage_;
	}
}

void BossEnemy::SpinAttack()
{
	if (spinAttackTimer_++ >= 100) {
		isSpinAttack_ = true;
	}
	if (spinAttackTimer_ >= 200) {
		spinAttackTimer_ = 0;
		isSpinAttack_ = false;
	}
	if (isSpinAttack_) {
		rotation_.x += 1.0f;
	}
	bossEnemyObj_->SetRotation(rotation_);
}
