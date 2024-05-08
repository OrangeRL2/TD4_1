/*
* MyGame.h
* ゲーム固有の処理全体
*/

#pragma once
#include "Framewark.h"
#include "SceneManager.h"

class MyGame : public Framewark
{
public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了
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

	SoundManager* soundManager_ = nullptr;

	//シーン
	BaseScene* scene_ = nullptr;

};

