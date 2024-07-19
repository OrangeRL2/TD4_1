/*
* TitleScene.h
* タイトルシーン全体の処理
*/

#pragma once
#include "SceneManager.h"

class TitleScene : public BaseScene
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, SoundManager* soundManager, SpriteCommon* spriteCommon, ViewProjection* viewPro) override;
	
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private:
	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	ImGuiManager imGui;
	SoundManager* soundManager_ = nullptr;
	SEManager* SE = nullptr;
	SpriteCommon* spriteCommon_ = nullptr;
	//ビュープロジェクション
	ViewProjection* viewProjection = nullptr;

	SceneManager* sceneManager_ = nullptr;


	//カメラ位置
	XMFLOAT3 cameraPos = { 0,0,-50 };
	//マウスポインター
	//XMFLOAT2 mousePos;

	//シーン切り替え演出
	std::unique_ptr<SceneChange> sceneChange;
	std::unique_ptr<Sprite> spaceSprite;
	std::unique_ptr<Sprite> titleSprite;

	//地面
	std::unique_ptr<Ground> ground;
	//背景オブジェクト
	std::unique_ptr<BackObject> coral;
	std::unique_ptr<BackObject> stone;
	//泡パーティクル
	std::unique_ptr<ParticleManager> bubble;

	//天球
	std::unique_ptr<Skydome> skydome;

	bool isUIDraw = true;
	const int MaxUITimer = 30;
	int UITimer = MaxUITimer;
};

