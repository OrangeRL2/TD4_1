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
}

void BossEnemy::Update()
{
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
	position_.x += move_.x;
	bossEnemyObj_->SetPosition(position_);
}
