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
	void DodgeEffect();

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
	const XMFLOAT3 cameraPosition = { 0.0f,25.0f,-30.0f };
	//カメラ位置
	const XMFLOAT3 goCameraPosition = { 0.0f,25.0f,-5.0f };
	//フレーム最大数
	const float frameMax = 60.0f;
	//ゲームオーバー時のカメライージング用フレーム
	float goCameraFrame = 0.0f;
	//スプライト
	std::unique_ptr<Sprite> cursorSprite;

  //オブジェクトリスト
  std::vector<Object3d*> blockWoodBoxList_;

	//ゲームオーバー画面
	std::unique_ptr<Gameover> gameover;
	std::unique_ptr<Clear> clear;

	//地面
	std::unique_ptr<Ground> ground;
	//背景オブジェクト
	std::unique_ptr<BackObject> coral;
	std::unique_ptr<BackObject> stone;
	std::unique_ptr<BackObject> seaweed;
	//泡パーティクル
	std::unique_ptr<ParticleManager> bubble;

	//天球
	std::unique_ptr<Skydome> skydome;

	//シーン切り替え演出
	std::unique_ptr<SceneChange> sceneChange;

	//ボスHPUI
	std::unique_ptr<Sprite> bossHPSprite;
};

