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
	DirectX::XMFLOAT3 angle = { 0.0f,0.0f,0.0f };

	float moveLim = 5.0f;
	float speedLim = 2.0f;
	float turnSpeed = 0.0f;
	float speed = 0.0f;
	float speedBoost = 0.0f;
	float gravity = 0.2f;


	//無敵時間
	const float invincibleTimerMax = 60.0f;
	float invincibleTimer = invincibleTimerMax;
	bool isInvincible = false;

	//ヒット判定
	bool isHit = false;

	//回避関連
	bool isDodge = false;
	const float accelaration = 0.0025f;
	float moveSpeed = 0;
	const float maxSpeed = 0.5;
	int isHitMap = false;

	//HP
	int hpMax = 2;
	int hp = hpMax;

};

