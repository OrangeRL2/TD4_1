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
#include "MyMath.h"
#include "ViewProjection.h"
#include "ParticleManager.h"
#include "DamageEffect.h"
#include <DirectXMath.h>

using namespace OogamiEngine;

class Afterimage
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(SpriteCommon* spCommon, ViewProjection* viewPro, XMFLOAT3 playerPos, XMFLOAT3 pRot);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(XMFLOAT3 position);

	/// <summary>
	/// 描画(3D)
	/// </summary>
	void Draw();
	void Delete();
	bool GetActive() { return isInactive; }
public:
	SpriteCommon* spriteCommon_ = nullptr;
	Input* input_ = nullptr;
	ViewProjection* viewProjection = nullptr;
	Model* model_ = nullptr;
	Model* bulletModel = nullptr;
	std::unique_ptr<Object3d> playerObject = nullptr;
private:
	DirectX::XMFLOAT3 position_ = { 10.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 move = { 10.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 scale = { 1.0f,1.0f,1.0f };
	DirectX::XMFLOAT3 velocity = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 startPosition = { 0.0f,-1.0f,0.0f };
	DirectX::XMFLOAT3 rot = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 finalRot = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 dodgeRot = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 angle = { 0.0f,0.0f,0.0f };

	bool isInactive = false;
	int time = 0;
	std::random_device rnd;
};

