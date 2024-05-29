/*
* BossEnemy.cpp
* ボスの挙動
*/

#include "BossEnemy.h"

#include "Input.h"

void BossEnemy::Initialize()
{
	// ボスの生成
	bossEnemyModel_ = Model::LoadFromOBJ("Box");
	bossEnemyObj_ = Object3d::Create();
	bossEnemyObj_->SetModel(bossEnemyModel_);
	bossEnemyObj_->SetPosition(position_);
	bossEnemyObj_->SetScale(scale_);
	bossEnemyObj_->SetRotation(rotation_);

	speed_ = 0.0f;
}

void BossEnemy::Update()
{
	Move();
	
	bossEnemyObj_->Update();
}

void BossEnemy::Draw()
{
	bossEnemyObj_->Draw();
}

void BossEnemy::Attack()
{
	if (isAttack_ == true) {

	}
}

void BossEnemy::Move()
{
	// ボスの移動
	move_.x = speed_ + speedBoost_;
	if (speed_ > speedLim_) {
		speed_ = speedLim_;
	}
	if (speed_ < speedLim_)
	{
		speed_ += 0.001f;
	}
	//動き
	if (OogamiEngine::Input::GetInstance()->PushKey(DIK_D)) {
		if (turnSpeed_ < 10.0f)
		{
			turnSpeed_ += 1.0f;
		}
		position_.y += gravity_;
	}
	//上に泳いでない時に下に動く
	else if (position_.y >= -moveLim_) {
		if (turnSpeed_ > -10.0f)
		{
			turnSpeed_ -= 1.0f;
		}
		position_.y -= gravity_;
	}
	
	position_.x += move_.x;
	position_.y += move_.y;
	position_.z += move_.z;
	bossEnemyObj_->SetPosition(position_);
	bossEnemyObj_->SetRotation(rotation_);
}
