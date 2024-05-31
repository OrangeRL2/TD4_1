/*
* BossEnemyBullet.h
* ボスの弾クラス
*/

#pragma once

#include "Object3d.h"
#include "Model.h"

class BossEnemyBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// オブジェクト
	Object3d* bossEnemyBulletObj_ = nullptr;
	Model* bossEnemyBulletModel_ = nullptr;

	// 座標、サイズ、回転
	DirectX::XMFLOAT3 position_ = { 0,0,0 };
	DirectX::XMFLOAT3 scale_ = { 1,1,1 };
	DirectX::XMFLOAT3 rotation_ = { 0,0,0 };

	DirectX::XMFLOAT3 velocity_ = { 0,0,0 };
	
	// デスフラグ
	bool isDead_ = false;
};