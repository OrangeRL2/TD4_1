/*
* Particle.h
* パーティクル一粒分の処理
*/

#pragma once
#include "Object3d.h"
#include "Input.h"

class Particle
{
public:
	~Particle();

	//DirectX::を省略
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;

	//パーティクル1粒
	struct OneGrain
	{
		//色
		XMFLOAT4 color = {};
		//座標
		XMFLOAT3 position = {};
		//回転
		XMFLOAT3 rotation = {};
		//速度
		XMFLOAT3 velocity = {};
		//加速度
		XMFLOAT3 accel = {};
		//現在フレーム
		float frame = 0;
		//終了フレーム
		float num_frame = 0;
		//スケール
		float scale = 1.0f;
		//初期値
		float s_scale = 1.0f;
		//最終値
		float e_scale = 0.0f;
		//順番
		int num = 0;

	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(DirectX::XMFLOAT3 moveVal, float gamespeed);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//ゲッター
	bool GetIsDead() { return isDead; }
	//セッター
	void SetColor(DirectX::XMFLOAT4 color) { object->SetColor(color); }

	OneGrain oneGrain;

private:
	std::unique_ptr<Object3d> object;

	bool isDead = false;
	XMFLOAT3 speed = { 1.0f,1.0f,1.0f };

};

