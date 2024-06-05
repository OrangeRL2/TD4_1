/*
* BossEnemy.h
* ボスの挙動
*/

#pragma once

#include "Object3d.h"
#include "Model.h"
#include "BossEnemyBullet.h"
#include "Sprite.h"
#include "SpriteCommon.h"

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
	void Update(const DirectX::XMFLOAT3& playerPosition);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack(const DirectX::XMFLOAT3& playerPosition);

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

public:
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns></returns>
	const DirectX::XMFLOAT3& GetPosition() const { return position_; }
	void SetPosition(const DirectX::XMFLOAT3& position) { position_ = position; }

	DirectX::XMFLOAT3 GetPosition() { return position_; }
private:
	Object3d* bossEnemyObj_ = nullptr;
	Model* bossEnemyModel_ = nullptr;

	std::list<std::unique_ptr<BossEnemyBullet>> bossEnemyBullet_;

	// ボスの座標、スケール、回転、移動量
	DirectX::XMFLOAT3 position_ = { 0.0f,-10.0f,5.0f };
	DirectX::XMFLOAT3 scale_ = { 2.0f,2.0f,2.0f };
	DirectX::XMFLOAT3 rotation_ = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 move_ = { 10.0f,0.0f,0.0f };

	// 攻撃フラグ
	bool isAttack_ = false;
	int attackTimer_ = 0;
	int time_ = 0;

	// スピード
	float speedAddition_ = 0.0f;
	float oldSpeed_ = 0.0f;
	float speed_ = 0.0f;
	float speedBoost_ = 0.0f;
	float speedLim_ = 2.0f;
	float moveLim_ = 5.0f;
	float gravity_ = 0.2f;

	// 定数
	const float playerDifference_ = 10.0f;
	const int attackCoolTime_ = 100;
};