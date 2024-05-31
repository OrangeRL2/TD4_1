/*
* BossEnemy.h
* ボスの挙動
*/

#pragma once

#include "Object3d.h"
#include "Model.h"
#include "BossEnemyBullet.h"

class BossEnemy
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	DirectX::XMFLOAT3 GetPosition() { return position_; }
private:
	Object3d* bossEnemyObj_ = nullptr;
	Model* bossEnemyModel_ = nullptr;

	std::list<std::unique_ptr<BossEnemyBullet>> bossEnemyBullet_;

	// ボスの座標、スケール、回転
	DirectX::XMFLOAT3 position_ = { 0,0,0 };
	DirectX::XMFLOAT3 scale_ = { 5,5,5 };
	DirectX::XMFLOAT3 rotation_ = { 0,0,0 };
};