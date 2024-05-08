/*
* SceneManager.h
* それぞれのシーンの管理
*/

#pragma once
#include "BaseScene.h"
#include "GamePlayScene.h"
#include "TitleScene.h"

class SceneManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(DirectXCommon* dxCommon, SoundManager* soundManager, SpriteCommon* spriteCommon, ViewProjection* viewPro);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 次シーン予約
	/// </summary>
	void SetNextScene(BaseScene* nextScene) { nextScene_ = nextScene; }

	//ゲッター
	bool GetEndReques() { return endRequest_; }

private:
	//実行中のシーン
	BaseScene* scene_ = nullptr;
	//次のシーン
	BaseScene* nextScene_ = nullptr;

	bool endRequest_ = false;
};

