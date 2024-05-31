/*
* BaseScene.h
* 各シーンのベース元
*/

#pragma once
#include "Input.h"
#include "ImGuiManager.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "SoundManager.h"
#include "Object3d.h"
#include "ViewProjection.h"
#include "Button.h"
#include "ParticleManager.h"
#include "NumberUI.h"
#include "DamageEffect.h"
#include <random>

//前方宣言
class SceneManager;

class BaseScene
{
public:

	virtual ~BaseScene() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize(DirectXCommon* dxCommon_, SoundManager* soundManager, SpriteCommon* spriteCommon, ViewProjection* viewPro);

	/// <summary>
	/// 終了処理
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

	//ゲッター
	virtual bool GetEndRequest() { return endRequst_; }
	SceneManager* GetSceneManager() { return sceneManager_; }
	//セッター
	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }
	virtual void SetEndRequest(bool endRequst) { endRequst_ = endRequst; }

private:
	//シーンマネージャ
	SceneManager* sceneManager_ = nullptr;
	//終了フラグ
	bool endRequst_ = false;
};

