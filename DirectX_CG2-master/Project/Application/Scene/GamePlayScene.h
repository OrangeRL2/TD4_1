/*
* GamePlayScene.h
* ゲームプレイシーン全体の処理
*/

#pragma once

#include "SceneManager.h"
#include "BossEnemy.h"

class GamePlayScene : public BaseScene
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon_, SoundManager* soundManager, SpriteCommon* spriteCommon, ViewProjection* viewPro) override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	
private:

	//ポインタ
	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	ImGuiManager imGui;
	SoundManager* soundManager_ = nullptr;
	SpriteCommon* spriteCommon_ = nullptr;

	SEManager* SE = nullptr;
	
	//マウスポインター
	XMFLOAT2 mousePos;

	//ビュープロジェクション
	ViewProjection* viewProjection = nullptr;

	std::unique_ptr<BossEnemy> bossEnemy_;
};

