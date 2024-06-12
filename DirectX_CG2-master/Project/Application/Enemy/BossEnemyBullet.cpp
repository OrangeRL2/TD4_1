/*
* BossEnemyBullet.cpp
* ボスの弾クラス
*/

#include "BossEnemyBullet.h"

void BossEnemyBullet::Initialize(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& velocity)
{
	// 値のセット
	this->velocity_ = velocity;
	this->position_ = position;

	// === ボスの弾の生成 === //
	bossEnemyBulletModel_ = Model::LoadFromOBJ("Box");
	bossEnemyBulletObj_ = Object3d::Create();
	bossEnemyBulletObj_->SetModel(bossEnemyBulletModel_);
	bossEnemyBulletObj_->SetPosition(position_);
	bossEnemyBulletObj_->SetScale(scale_);
	bossEnemyBulletObj_->SetRotation(rotation_);
}

void BossEnemyBullet::Update()
{
	// === ボスの弾の更新 === //
	bossEnemyBulletObj_->Update();
}

void BossEnemyBullet::Draw()
{
	// === ボスの弾の描画 === //
	bossEnemyBulletObj_->Draw();
}