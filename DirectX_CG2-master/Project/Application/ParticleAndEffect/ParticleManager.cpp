/*
* ParticleManager.cpp
* パーティクル複数の処理
*/

#include "ParticleManager.h"
#include "MyMath.h"

ParticleManager::~ParticleManager() {

}

void ParticleManager::Initialize(Model* model) {

	model_ = model;


}

void ParticleManager::UpdateAlways(bool isActive, int inter) {
	//寿命が尽きたパーティクルを全削除
	particle.remove_if([](std::unique_ptr<Particle>& p) {
		return p->GetIsDead();
		});

	if (isActive) {
		interval--;

		if (interval <= 0) {

			std::unique_ptr<Particle>p = std::make_unique<Particle>();

			p->Initialize(model_);
			p->oneGrain.num_frame = oneGrain.num_frame;
			p->oneGrain.position = oneGrain.position;
			p->oneGrain.velocity = oneGrain.velocity;
			p->oneGrain.accel = oneGrain.accel;
			p->oneGrain.s_scale = oneGrain.s_scale;
			p->oneGrain.e_scale = oneGrain.e_scale;
			p->SetColor(oneGrain.color);

			//パーティクルを登録する
			particle.push_back(std::move(p));

			//発生間隔をリセット
			interval = inter;
		}

	}


	for (std::unique_ptr<Particle>& p : particle) {

		p->Update(1.0f);

	}
}

void ParticleManager::AddAlways(float life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale, XMFLOAT4 color) {
	oneGrain.num_frame = life;
	oneGrain.position = position;
	oneGrain.velocity = velocity;
	oneGrain.accel = accel;
	oneGrain.s_scale = start_scale;
	oneGrain.e_scale = end_scale;
	oneGrain.color = color;
}

void ParticleManager::UpdateHit(float gamespeed) {
	//寿命が尽きたパーティクルを全削除
	particle.remove_if([](std::unique_ptr<Particle>& p) {
		return p->GetIsDead();
		});

	for (std::unique_ptr<Particle>& p : particle) {
		p->Update(gamespeed);
	}

}

void ParticleManager::AddHit(Model* model, int amount, float life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale, XMFLOAT4 color) {
	//model_ = model;

	for (int i = 0; i <= amount; i++) {

		std::unique_ptr<Particle>p = std::make_unique<Particle>();

		//速度をランダム化
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * velocity.x - velocity.x / 2.0f;
		vel.y = (float)rand() / RAND_MAX * velocity.y / 2.0f;
		vel.z = (float)rand() / RAND_MAX * velocity.z - velocity.z / 2.0f;

		//加速度
		XMFLOAT3 acc{};
		acc.x = accel.x * vel.x * MyMath::RandomFloat(0.0f, 1.0f);
		acc.y = accel.y * vel.y * MyMath::RandomFloat(0.0f, 1.0f);
		acc.z = accel.z * vel.z * MyMath::RandomFloat(0.0f, 1.0f);

		//数値を登録
		p->Initialize(model);
		p->oneGrain.num_frame = MyMath::RandomFloat(life, life + 10.0f);
		p->oneGrain.position = position;
		p->oneGrain.rotation = vel;
		p->oneGrain.velocity = vel;
		p->oneGrain.accel = accel;
		p->oneGrain.s_scale = start_scale;
		p->oneGrain.e_scale = end_scale;
		p->SetColor(color);

		//パーティクルを登録する
		particle.push_back(std::move(p));
	}
}

void ParticleManager::Draw() {
	for (std::unique_ptr<Particle>& p : particle) {
		p->Draw();
	}
}
