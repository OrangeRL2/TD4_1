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
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

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

private:
	Object3d* bossEnemyObj_ = nullptr;
	Model* bossEnemyModel_ = nullptr;

	std::list<std::unique_ptr<BossEnemyBullet>> bossEnemyBullet_;

	// ボスの座標、スケール、回転、移動量
	DirectX::XMFLOAT3 position_ = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 scale_ = { 2.0f,2.0f,2.0f };
	DirectX::XMFLOAT3 rotation_ = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 move_ = { 10.0f,0.0f,0.0f };

	// 攻撃フラグ
	bool isAttack_ = false;

	// スピード
	float speed_ = 0.0f;
	float speedBoost_ = 0.0f;
	float speedLim_ = 2.0f;
	float moveLim_ = 5.0f;
	float turnSpeed_ = 0.0f;
	float gravity_ = 0.2f;

	//無敵時間
	const float invincibleTimerMax_ = 60.0f;
	float invincibleTimer_ = invincibleTimerMax_;
	bool isInvincible_ = false;
};