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
	DirectX::XMFLOAT3 position = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 scale = { 1.0f,1.0f,1.0f };
	DirectX::XMFLOAT3 velocity = { 0,0,0 };
	DirectX::XMFLOAT3 startPosition = { 0.0f,-1.0f,0.0f };
	DirectX::XMFLOAT3 rot = { 0.0f,0.0f,0.0f };
};

