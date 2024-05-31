/*
* GamePlayScene.h
* ゲームプレイシーン全体の処理
*/

#pragma once

#include "SceneManager.h"
#include "StageField.h"
#include "BossEnemy.h"
#include "Player.h"
#include "Item.h"

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

	void Collision();

	
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

  //ステージフィールド
  std::unique_ptr< StageField > stageField_;
	std::unique_ptr<BossEnemy> bossEnemy_;
	std::unique_ptr<Player> player;
	std::unique_ptr<Item> item_;

	//カメラ位置
	const XMFLOAT3 cameraPosition = { 0.0f,25.0f,-12.0f };

	//スプライト
	std::unique_ptr<Sprite> cursorSprite;
};

