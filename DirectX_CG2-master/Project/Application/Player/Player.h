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
#include "SEManager.h"
#include "WinApp.h"
#include "ViewProjection.h"
#include "ParticleManager.h"
#include "DamageEffect.h"
#include "Afterimage.h"
#include "DodgeEffect.h"
#include "PlayerHP.h"
#include "PlayerStamina.h"
#include <DirectXMath.h>

using namespace OogamiEngine;

enum EFFECT {
	heal,
	maxHeal,
	slow,
	staminaUp,
	staminaMax,
	speedUp,
	speedLimUp,
	invincible,
	invincibleOff,
};

class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(SpriteCommon* spCommon, ViewProjection* viewPro, SEManager* SE);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画(3D)
	/// </summary>
	void Draw();

	/// <summary>
	/// 描画(2D)
	/// </summary>
	void Draw2D();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();
	/// <summary>
	/// 回避
	/// </summary>
	void Dodge();
	void DodgeActive();
	void Dodge2();
	void DodgeOnHit();

	void ItemEffect(enum EFFECT effect);

	/// <summary>
	/// 接触時の処理
	/// </summary>
	void OnCollision(const int dmg);
	//ゲッター
	DirectX::XMFLOAT3 GetPosition() { return position; }
	DirectX::XMFLOAT3 GetScale() { return scale; }
	int GetHP() { return hp; }
	bool GetDodge() { return isDodgeInvincible; }
	const bool GetMove() { return moveFlag; }
	const bool GetEaseingFlag() { return easingFlag; }
	float GetCameraPos() { return cameraPosZ; }
	float GetSpaceTimer() { return spaceTimer; }
	float GetInvincibleTimer() { return invincibleTimer; }
	bool GetInvincibleFlag() { return isInvincible; }
	float GetSpeedLim() { return speedLim; }
public:
	SEManager* se = nullptr;
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
	float speedLim = 0.45f;
	float turnSpeed = 0.0f;
	float turnDodgeUp = 0.0f;
	float turnDodgeDown = 0.0f;
	float speed = 0.0f;
	float speedBoost = 0.0f;
	float gravity = 0.2f;

	float cameraPosZ = 0.0f;

	float MoveSpeedUp = 0.0f;
	float MaxSpeedUp = 20.0f;
	float acceleration = 0.002f;
	float MoveSpeedDown = 0.0f;
	float MaxSpeedDown = 20.0f;
	float accelerationDown = 0.001f;
	bool moveFlag = false;
	//dodge2
	float staminaTimer = 600.0f;
	float spaceTimer = 0.0f;
	float frame = 0.0f;
	int easingFlag = 0;
	float endFrame = 20.0f;
	float startX = 20.0f;
	float endX = 500.0f;
	float x = 0.0f;
	int afterFlag[200] = {};
	float easingPos = 0.0f;
	//ヒット判定
	bool isHit = false;
	//無敵時間
	const float invincibleTimerMax = 120.0f;
	float invincibleTimer = invincibleTimerMax;
	bool isInvincible = true;


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
	int hpMax = 6;
	int hp = hpMax;

	std::unique_ptr<ParticleManager> particle;
	std::unique_ptr<ParticleManager> dodgeParticle;
	std::unique_ptr<DamageEffect> damageEffect;
	std::unique_ptr<PlayerHP> HP;
	std::unique_ptr<PlayerStamina> stamina;
	std::list<std::unique_ptr<Afterimage>> afterimage_;
	std::list<std::unique_ptr<DodgeEffect>> dodgeEffect_;

	std::random_device rnd;

};