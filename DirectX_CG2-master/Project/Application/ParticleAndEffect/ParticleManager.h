/*
* ParticleManager.h
* パーティクル複数の処理
*/

#pragma once
#include "Particle.h"
#include "Object3d.h"

class ParticleManager
{
public:
	~ParticleManager();

	//DirectX::を省略
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新(恒常パーティクル)
	/// </summary>
	void UpdateAlways(int interval, bool isActive, bool isBubble);

	/// <summary>
	/// 更新(ヒットパーティクル)
	/// </summary>
	void UpdateHit(float gamespeed, bool isBubble);
	
	/// <summary>
	/// 回転パーティクル更新
	/// </summary>
	void UpdateSpin(XMFLOAT3 position, float gamespeed);

	/// <summary>
	/// 恒常パーティクル一粒を発生
	/// </summary>
	void AddAlways(XMFLOAT3 position,float start_scale, float life, XMFLOAT4 color = { 1,1,1,1 }, XMFLOAT3 velocity = {1,1,1}, XMFLOAT3 accel = {-0.05f,-0.05f,-0.05f});
	/// <summary>
	/// ヒットパーティクル発生
	/// </summary>
	void AddHit(XMFLOAT3 position, float start_scale, float life, int amount, XMFLOAT4 color = { 1,1,1,1 }, XMFLOAT3 velocity = { 1,1,1 }, XMFLOAT3 accel = { -0.05f,-0.05f,-0.05f });
	/// <summary>
	/// 回転パーティクル発生
	/// </summary>
	void AddSpin(XMFLOAT3 position, float start_scale, float life, float cRange, int amount, bool colorful);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	Model* model_;
	ViewProjection* viewProjection_;

	//パーティクル配列
	std::list<std::unique_ptr<Particle>>particle;
	//パーティクル一粒
	Particle::OneGrain oneGrain;
	//発生間隔
	int interval_;

	//泡パーティクルのランダム移動量
	float bubbleMoveVal = 0.5f;
	//泡パーティクルの浮力
	float bubbleBuoyancy = 0.5f;

	//回転量
	float rotVal = 0.025f;
	float rot = 0.0f;

	//回転の大きさ
	float circleRange = 1.0f;

	//パーティクル量
	int particleAmount = 0;

	XMFLOAT4 randomColor = { 1,1,1,1 };
	XMFLOAT3 spinPos = { 0,0,0 };

};

