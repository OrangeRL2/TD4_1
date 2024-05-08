/*
* Button.h
* ボタンUIの処理
*/

#pragma once
#include "Input.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "DirectXCommon.h"
#include "SEManager.h"
using namespace OogamiEngine;

class Button
{
public:

	///<summary>初期化</summary>
	void Initialize(Input* input, SpriteCommon* spriteCommon, int index);

	///<summary>更新</summary>
	void UpdateMouse(DirectX::XMFLOAT2 mouse);
	void Update(DirectX::XMFLOAT2 pos,float size);

	///<summary>マウスカーソルとの判定</summary>
	void MouseCollision(DirectX::XMFLOAT2 mouse);

	///<summary>描画</summary>
	void Draw();

	//ゲッター
	bool GetIsPush() { return isPush; }

private:
	SEManager* se_ = nullptr;
	SpriteCommon* spriteCommon_ = nullptr;
	Sprite* sprite_ = nullptr;
	Input* input_ = nullptr;

	bool isPush = false;
	bool isSoundPlay = false;
	DirectX::XMFLOAT2 size_ = { 0.0f,0.0f };
};

