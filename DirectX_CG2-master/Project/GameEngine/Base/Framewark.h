/*
* FrameWark.h
* ゲームの枠組み
*/

#pragma once
#include "SceneManager.h"
#include "FbxLoader.h"
#include "PostEffect.h"
#include "SpriteCommon.h"
#include "SpriteManager.h"

class Framewark
{
public:
  ////モデル名
  //enum modelName {
  //  modelWoodBox_
  //};

public://メンバ関数

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~Framewark() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 終了チェック
	/// </summary>
	virtual bool IsEndRequst() { return endRequst_; }

	/// <summary>
	/// 実行
	/// </summary>
	void Run();

	//ゲッター
	WinApp* GetWinApp() { return winApp; }
	DirectXCommon* GetDxCommon() { return dxCommon_; }
	Input* GetInput() { return input; }
	ViewProjection* GetViewPro() { return viewProjection; }
	SceneManager* GetSceneManager() { return sceneManager_; }

private://メンバ変数
	//ポインタ
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input = nullptr;
	ViewProjection* viewProjection = nullptr;

	//シーンマネージャー
	SceneManager* sceneManager_ = nullptr;

	//スプライト
	SpriteCommon* spriteCommon_ = nullptr;
	SpriteManager* SPManager = nullptr;
	Sprite* SP = nullptr;


	//サウンドマネージャー
	SoundManager* soundManager_ = nullptr;

	//終了チェック
	bool endRequst_ = false;

	//フルスクリーン
	bool fullScreen = false;

};

