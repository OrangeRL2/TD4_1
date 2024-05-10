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
	void UpdateAlways(bool isActive, int interval);
	/// <summary>
	/// 更新(ヒットパーティクル)
	/// </summary>
	void UpdateHit(float gamespeed);

	/// <summary>
	/// 恒常パーティクル一粒を発生
	/// </summary>
	void AddAlways(float life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale, XMFLOAT4 color = {1,1,1,1});
	/// <summary>
	/// ヒットパーティクル発生
	/// </summary>
	void AddHit(Model* model, int amount, float life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale, XMFLOAT4 color = {1,1,1,1});

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
	int interval;

};

