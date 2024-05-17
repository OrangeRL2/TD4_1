/*
* BossEnemy.cpp
* ボスの挙動
*/

#include "BossEnemy.h"

void BossEnemy::Initialize()
{
	bossEnemyObj_ = Object3d::Create();
	bossEnemyModel_ = Model::LoadFromOBJ("Box");
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
}
