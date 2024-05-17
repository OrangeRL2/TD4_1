/*
* BossEnemyBullet.cpp
* ボスの弾クラス
*/

#include "BossEnemyBullet.h"

void BossEnemyBullet::Initialize()
{
	bossEnemyBulletModel_ = Model::LoadFromOBJ("Box");
	bossEnemyBulletObj_ = Object3d::Create();
	bossEnemyBulletObj_->SetModel(bossEnemyBulletModel_);
	bossEnemyBulletObj_->SetPosition(position_);
	bossEnemyBulletObj_->SetScale(scale_);
	bossEnemyBulletObj_->SetRotation(rotation_);
}

void BossEnemyBullet::Update()
{
	bossEnemyBulletObj_->Update();
}

void BossEnemyBullet::Draw()
{
	bossEnemyBulletObj_->Draw();
}
