/*
* BossEnemyBullet.cpp
* ボスの弾クラス
*/

#include "BossEnemyBullet.h"

void BossEnemyBullet::Initialize(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& velocity)
{
	this->velocity_ = velocity;

	bossEnemyBulletModel_ = Model::LoadFromOBJ("Box");
	bossEnemyBulletObj_ = Object3d::Create();
	bossEnemyBulletObj_->SetModel(bossEnemyBulletModel_);
	position_ = position;
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