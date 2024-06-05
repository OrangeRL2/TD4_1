/*
* Player.h
* 自機の処理
*/

#pragma once
#include "Sprite.h"
#include <list>
#include <random>
#include "Input.h"
#include "Model.h"
#include "Object3d.h"
#include "WinApp.h"
#include "ViewProjection.h"
#include "ParticleManager.h"
#include "DamageEffect.h"
#include <DirectXMath.h>

using namespace OogamiEngine;

class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(SpriteCommon* spCommon, ViewProjection* viewPro);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画(3D)
	/// </summary>
	void Draw();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();
	/// <summary>
	/// 回避
	/// </summary>
	void Dodge();

	/// <summary>
	/// 接触時の処理
	/// </summary>
	void OnCollision(const int dmg);
	//ゲッター
	DirectX::XMFLOAT3 GetPosition() { return position; }
	DirectX::XMFLOAT3 GetScale() { return scale; }
	int GetHP() { return hp; }

public:
	SpriteCommon* spriteCommon_ = nullptr;
	Input* input_ = nullptr;
	ViewProjection* viewProjection = nullptr;
	Model* model_ = nullptr;
	Model* bulletModel = nullptr;
	std::unique_ptr<Object3d> playerObject = nullptr;
private:
	DirectX::XMFLOAT3 position = { 10.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 move = { 10.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 scale = { 1.0f,1.0f,1.0f };
	DirectX::XMFLOAT3 velocity = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 startPosition = { 0.0f,-1.0f,0.0f };
	DirectX::XMFLOAT3 rot = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 finalRot = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 dodgeRot = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 angle = { 0.0f,0.0f,0.0f };

	float moveLim = 10.0f;
	float speedLim = 2.0f;
	float turnSpeed = 0.0f;
	float speed = 0.0f;
	float speedBoost = 0.0f;
	float gravity = 0.2f;


	//ヒット判定
	bool isHit = false;
	//無敵時間
	const float invincibleTimerMax = 60.0f;
	float invincibleTimer = invincibleTimerMax;
	bool isInvincible = false;

	
	//回避関連
	bool isDodge = false;
	bool isDodgeInvincible = false;
	const float dodgeTimerMax = 60.0f;
	float dodgeTimer = dodgeTimerMax;
	const float accelaration = 0.2025f;
	float moveSpeed = 0;
	const float maxSpeed = 2.5;
	int isHitMap = false;

	//HP
	int hpMax = 5;
	int hp = hpMax;

	std::unique_ptr<ParticleManager> particle;
	std::unique_ptr<DamageEffect> damageEffect;
};

