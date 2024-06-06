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

};

